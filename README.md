# Dodoi-Engine Wii - version 0.29.1

A lightweight 2D game engine for **Nintendo Wii** homebrew, built in C17 using the [devkitPPC](https://devkitpro.org/) toolchain and SDL2.

Developed by **Hudson Schumaker** — [Dodoi-Lab](http://dodoi-lab.com:8080/) © 2024

---

## Features

- **Scene system** — lifecycle callbacks (`load`, `input`, `update`, `render`, `run`, `unload`) with clean scene transitions
- **2D Graphics** — SDL2-backed renderer, color utilities, horizontal & vertical parallax scrolling
- **ECS** — lightweight, struct-of-arrays entity/component system (transform, texture, animation) with tags and simple systems (render, radar, animation)
- **Sprite animation** — named clips sliced from horizontal sprite-strip textures, with looping, flipping, and per-entity playback state
- **Game Objects** — position, size, z-ordering, active flag, and AABB box-collider support
- **Sound & Music** — load/play/pause/stop via SDL2_mixer (supports `.wav` and `.ogg`)
- **Input** — per-frame GameCube controller (PAD) snapshot with down/held/up button state and analog sticks/triggers
- **UI Widgets** — button, image, and label components
- **Math utilities** — LUT-based sin/cos/atan tables, fast inverse sqrt, `vec2_t` vector math, for performance on fixed-point hardware
- **Tile maps** — grid and map helpers with configurable tile sizes
- **Smooth delta time** — exponential moving-average frame timing, capped at 250 ms
- **Camera** — 2D camera system

---

## Project Structure

```
src/
├── de-wii/
|      ├── core/  # Engine init/quit, context (window + renderer), camera, input, collision
|      ├── ecs/   # Entity manager, transform/texture components, render & radar systems
|      ├── gfx/   # Scene, graphics helpers, parallax scrolling
|      ├── sfx/   # Sound effects and music (SDL_mixer)
|      ├── ui/    # Button, image, label widgets
|      ├── math/  # 2D math with LUT-based trigonometry
|      ├── util/  # Grid, tile-map, and isometric projection utilities
└── playground/   # Splash screen and level prototypes
data/             # Binary assets (images, audio, fonts) embedded at build time
build/            # Intermediate object files (generated)
bin/              # Output .elf / .dol binaries (generated)
```

---

## Requirements

| Tool | Notes |
|------|-------|
| [devkitPro](https://devkitpro.org/wiki/Getting_Started) | Install the `wii-dev` group |
| `DEVKITPPC` env var | Must point to your devkitPPC installation |
| SDL2 port libs | `gamecube-sdl2`, `gamecube-sdl2_ttf`, `gamecube-sdl2_gfx`, `gamecube-sdl2_mixer`, `gamecube-sdl2_image` |
| freetype2 | Bundled via devkitPro portlibs |

---

## Building

```sh
# Set the devkitPPC path (add to your shell profile)
export DEVKITPPC=/opt/devkitpro/devkitPPC

make        # Build → produces bin/<project>.elf and bin/<project>.dol
make clean  # Remove build artefacts
```

The `.dol` file can be run on real hardware via a loader (e.g. SD Gecko + Swiss) or in an emulator such as [Dolphin](https://dolphin-emu.org/).

---

## API Usage

All engine headers are reachable from `src/de-wii/`. The snippets below are trimmed from the real `src/playground/` example project.

### Engine lifecycle

Every game starts by initializing the engine, runs one or more scenes, then quits:

```c
#include "de-wii/core/engine.h"

int main(int argc, char **argv) {
    engine_init();

    my_scene_init();
    my_scene_get_scene()->load();
    my_scene_get_scene()->run();
    my_scene_get_scene()->unload();

    engine_quit();
    return 0;
}
```

`engine_calculate_delta_time()` / `engine_get_delta_time()` return the smoothed frame delta (seconds) for use in `update()`.

### Delta time (`de-wii/core/engine.h`)

`engine_calculate_delta_time()` measures the time since it was last called (via `SDL_GetPerformanceCounter`), clamps it to 250 ms (`MAX_DT`) so a stall or breakpoint can't produce a huge jump, then blends it into a running average with an exponential moving average (`smooth_dt += 0.08 * (dt - smooth_dt)`) to iron out frame-to-frame jitter:

```c
void my_scene_update(void) {
    f32 dt = engine_calculate_delta_time(); // recomputes AND stores the new smoothed value
    transforms->px[e] += velocity_x * dt;
}

void my_scene_render(void) {
    f32 dt = engine_get_delta_time(); // re-reads the value stored by the last calculate() call, no recomputation
}
```

Call `engine_calculate_delta_time()` exactly once per frame — normally at the top of `update()` — since each call advances the internal clock. Use `engine_get_delta_time()` anywhere else in that same frame (e.g. `render()`) that needs the value without ticking the clock again.

### Scenes

A `scene_t` (`de-wii/gfx/scene.h`) is a plain struct of function pointers plus a `camera_t`. Wire it up once, then drive the loop from your own `run()`:

```c
#include "de-wii/gfx/scene.h"
#include "de-wii/gfx/gfx.h"
#include "de-wii/core/engine.h"
#include "de-wii/core/context.h"
#include "logo_png.h"

static bool running = false;
static scene_t* my_scene = NULL;
static SDL_Texture* logo = NULL;
static SDL_Rect logo_rect = { 0, 0, 0, 0 };

void my_scene_init(void) {
    my_scene = malloc(sizeof(scene_t));
    
    // necessary if the scene will use the render_system
    scene_init(my_scene); // sets the camera at(0,0) and w = WINDOW_WIDTH, h = WINDOW_HEIGHT and color black;
    my_scene->load   = my_scene_load;
    my_scene->input  = my_scene_input;
    my_scene->update = my_scene_update;
    my_scene->render = my_scene_render;
    my_scene->run    = my_scene_run;
    my_scene->unload = my_scene_unload;
}

void my_scene_load(void) {
    logo = gfx_load_texture(logo_png, logo_png_size);
    SDL_QueryTexture(logo, NULL, NULL, &logo_rect.w, &logo_rect.h);
    running = true;
}

void my_scene_input(void) { /* poll input_update() here */ }

void my_scene_update(void) {
    f32 dt = engine_calculate_delta_time();
    // move things using dt...
}

void my_scene_render(void) {
    scene_begin_render();
    {
        SDL_RenderCopy(ctx_get_renderer(), logo, NULL, &logo_rect);
    }
    scene_end_render();
}

u8 my_scene_run(void) {
    while (running) {
        my_scene_input();
        my_scene_update();
        my_scene_render();
    }
    return 1;
}

void my_scene_unload(void) {
    SDL_DestroyTexture(logo);
    free(my_scene);
    my_scene = NULL;
}

scene_t* my_scene_get_scene(void) { return my_scene; }
```

You can also hand a scene to `scene_set_scene(scene_t* scene)`, which unloads the previously active scene (if any) before loading and running the new one.

### Graphics (`de-wii/gfx/gfx.h`, `color.h`)

```c
#include "de-wii/gfx/gfx.h"

// Load a texture from an embedded asset (see data/ + build/*.h)
SDL_Texture* tex = gfx_load_texture(sprite_png, sprite_png_size);

// Or get a texture_t with width/height already resolved
texture_t sprite = gfx_load_texture_ex(sprite_png, sprite_png_size);

// Cached variant: reuses one SDL_Texture for repeated loads of the same
// source data (handy when many entities share one sprite sheet)
texture_t shared = gfx_load_texture_cached(sprite_png, sprite_png_size);
gfx_clear_texture_cache(); // call when the owning scene unloads

gfx_render_texture(tex, x, y, w, h);
gfx_render_texture_rotated(tex, x, y, w, h, angle_degrees);

// Text
SDL_Texture* label = gfx_create_text(font_ttf, font_ttf_size, "Score: 10", 24, color_white());

// Primitives
gfx_draw_line(0, 0, 100, 100, color_red());
gfx_draw_circle(160, 120, 20, color_yellow());
gfx_draw_fill_box((SDL_Rect){ 10, 10, 64, 64 }, color_blue());
gfx_draw_triangle(0, 0, 32, 0, 16, 32, color_green());
```

### Input (`de-wii/core/input.h`)

Call `input_update()` once per frame, then query button/stick state for up to `INPUT_MAX_PADS` controllers:

```c
#include "de-wii/core/input.h"

void my_scene_input(void) {
    input_update();

    if (input_button_down(0, PAD_BUTTON_A)) {
        // fired the frame A was pressed
    }
    if (input_button_held(0, PAD_BUTTON_B)) {
        // held across frames
    }

    const pad_state_t* pad = input_get_pad(0);
    f32 dx = pad->stick.x; // [-1, 1], dead zone already applied
    f32 dy = pad->stick.y;
}
```

### Sound & Music (`de-wii/sfx/sfx.h`)

```c
#include "de-wii/sfx/sfx.h"
#include "ok_wav.h"

Mix_Chunk* sfx = sfx_load_sound(ok_wav, ok_wav_size);
sfx_play_sound(sfx);

Mix_Music* music = sfx_load_music(theme_ogg, theme_ogg_size);
sfx_play_music(music, -1); // loop forever
sfx_pause_music();
sfx_unpause_music();
sfx_stop_music();
```

### Camera & Collision (`de-wii/core/camera.h`, `collision.h`)

```c
#include "de-wii/core/camera.h"
#include "de-wii/core/collision.h"

camera_t camera = camera_new(color_white()); // set as scene.camera

if (rect_intersects(ax, ay, aw, ah, bx, by, bw, bh)) {
    // AABB overlap
}
if (circle_intersects(pos_a, radius_a, pos_b, radius_b)) {
    // circle overlap
}
```

### ECS — Entities & Components (`de-wii/ecs/`)

Entities are plain `u16` indices; components are struct-of-arrays pools sized to `MAX_ENTITIES`, owned by the engine and fetched via `engine_get_*()`:

```c
#include "de-wii/core/engine.h"
#include "de-wii/ecs/entity_manager.h"
#include "de-wii/ecs/render_system.h"
#include "de-wii/ecs/radar_system.h"

// Create a tagged entity
entity_manager_t* em = engine_get_entity_manager();
entity_t tower = entity_create_w_tag(em, TAG_TOWER);

// Position/scale/rotation/z-index
transform_pool_t* transforms = engine_get_transform_pool();
transforms->px[tower] = 160.0f;
transforms->py[tower] = 192.0f;
transforms->sx[tower] = transforms->sy[tower] = 1.0f;

// Sprite
texture_pool_t* textures = engine_get_texture_pool();
texture_t t1 = gfx_load_texture_ex(t1_png, t1_png_size);
textures->w[tower] = t1.w;
textures->h[tower] = t1.h;
textures->texture[tower] = t1.texture;

// Per-frame, in render()/update():
render_system(engine_get_transform_pool(), engine_get_texture_pool(), &camera);
radar_system(TAG_TOWER, TAG_ENEMY); // proximity checks between two tags
```

Available tags: `TAG_NONE`, `TAG_PLAYER`, `TAG_ENEMY`, `TAG_PROJECTILE`, `TAG_POWERUP`, `TAG_TOWER`.

### Animation (`de-wii/ecs/animation_controller.h`)

An animation clip is a horizontal sprite-strip texture sliced into equal-width frames. Each entity can own up to `MAX_ANIMATIONS_PER_ENTITY` named clips, one of which plays at a time; the active clip's current frame is synced into the entity's `texture_pool_t` (texture, size, source rect, flip) automatically:

```c
#include "de-wii/core/engine.h"
#include "de-wii/ecs/animation_controller.h"
#include "hoshi-move-right_png.h"

// In load(): register a clip and start playing it
animation_controller_pool_t* anim = engine_get_animation_controller_pool();
animation_controller_add(anim, hoshi, "move-right", hoshi_move_right_png, hoshi_move_right_png_size,
                          8 /* frames */, 100 /* ms per frame */, true /* loop */);
animation_controller_play(anim, hoshi);

// Switch clips by name/index, or replay the active one
animation_controller_play_by_name(anim, hoshi, "idle-right");
animation_controller_play_by_index(anim, hoshi, 0);
animation_controller_stop(anim, hoshi);
animation_controller_set_flip(anim, hoshi, true); // mirror horizontally

// In update(): advance frames and sync the texture pool
animation_system(engine_get_animation_controller_pool(), engine_get_texture_pool());

// In render(): draw as usual, render_system() honors the animation's source rect/flip
render_system(engine_get_transform_pool(), engine_get_texture_pool(), &camera);

// In unload(): free the clip textures and drop the entity
animation_controller_clear(engine_get_animation_controller_pool(), hoshi);
entity_destroy(engine_get_entity_manager(), hoshi);
```

### UI Widgets (`de-wii/ui/`)

Buttons, images, and labels are small standalone structs (not ECS entities) — construct on the stack or heap, set a source, render each frame:

```c
#include "de-wii/ui/button.h"
#include "de-wii/ui/label.h"
#include "hand_png.h"
#include "HemiHead_ttf.h"

button_t play_btn = button(100, 200);
button_set_source(&play_btn, hand_png, hand_png_size);
button_set_onclick(&play_btn, on_play_clicked);
play_btn.pad_button = PAD_BUTTON_A;
play_btn.visible = true;

label_t score = label(10, 10, "Score: 0");
label_set_font_size(&score, 16, HemiHead_ttf, HemiHead_ttf_size);
label_set_color(&score, color_white());

// In render():
button_render(&play_btn);
label_render(&score);

// In unload():
label_release(&score); // frees texture/text, not the struct itself (stack-allocated)
```

`image_t` follows the same pattern as `button_t` (`image()`/`image_new()`, `image_set_source()`, `image_set_tint()`, `image_render()`). Use the `_new`/`_destroy` heap variants (`button_new`, `image_new`, `label_new`) when a widget needs to outlive its creating scope.

### Math (`de-wii/math/math2d.h`)

```c
#include "de-wii/math/math2d.h"

vec2_t a = vec2_create(1.0f, 0.0f);
vec2_t b = vec2_add(a, vec2_up());
f32 dist = vec2_distance(a, b);

i32 angle = degrees_to_index(45.0f); // LUT index in [0, 1024)
f32 s = de_sinf(angle);
f32 c = de_cosf(angle);

f32 clamped = clampf(value, 0.0f, 1.0f);
```

### Tile maps (`de-wii/util/map.h`)

```c
#include "de-wii/util/map.h"

static const char* data[MAP_HEIGHT][MAP_WIDTH] = { /* "g0", "p1", ... */ };

map_t map;
map_load(&map, data);
map.textures[0] = gfx_load_texture(grass_png, grass_png_size);
map.textures[1] = gfx_load_texture(path_png, path_png_size);

// In render():
map_render(&map);
```

### Isometric grids (`de-wii/util/iso.h`)

For 2:1 diamond-projection maps, convert between grid coordinates and screen pixels:

```c
#include "de-wii/util/iso.h"

iso_grid_t grid = iso_grid(64, 32); // tile diamond is 64px wide, 32px tall

vec2_t screen_pos = iso_to_screen(grid, col, row); // grid -> pixel position, for rendering

vec2_t frac = screen_to_iso(grid, mouse_x, mouse_y); // pixel -> fractional grid coord
i32 picked_col = (i32)floorf(frac.x);
i32 picked_row = (i32)floorf(frac.y); // e.g. for cursor/tile picking
```

---

## License

This project is licensed under the terms found in [LICENSE](LICENSE).
