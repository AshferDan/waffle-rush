[README.md](https://github.com/user-attachments/files/35165419/README.md)
# WAFFLE RUSH

A 2D pixel-art platformer about a waffle on the run. As well as running and wall jumping, you can **crawl inside syrup platforms** to take routes a normal jump can't reach.

![WAFFLE RUSH gameplay](docs/gameplay.gif)

**[▶ Download the game, trailer and artwork (Google Drive)](https://drive.google.com/drive/folders/1oJzChbCfwYuX9dZuXOLY6yLIySLj2E0H?usp=sharing)** · Windows

---

## About

| | |
|---|---|
| **Genre** | 2D platformer |
| **Built with** | C, CProcessing |
| **Team** | 5 students, Avid Waffle Enjoyers |
| **Course** | CSD1401, Singapore Institute of Technology × DigiPen |
| **Timeline** | Sep–Dec 2024 (our first university project) |
| **Scope** | 5 levels, 11 character and hazard animations, 3 playtest sessions |

## My role: Tan Jun Quan

**Team lead, gameplay programmer, and pixel artist**

- **Led the 5-person team on our first university project.** Broke the game into tasks, drafted how each one should work (pseudocode and high-level overviews), and assigned them across the team. Wrote 153 of the team's 274 commits.
- **Set up the project.** Created the Visual Studio solution, integrated CProcessing, and wrote the first versions of the core files (`main.c`, `game.c`, `platform.c`, `utils.c`).
- **Built the platform-crawling mechanic.** The player can crawl *inside* syrup platforms. Each platform is built as a hollow outline of colliders instead of a solid box, with the player's hitbox sized slightly smaller than the inside. Pressing `E` moves the player through the wall, and the enter and exit animations make it look like crawling in.
- **Built wall sliding and wall jumping.** Holding toward a wall slows your fall. Jumping while sliding launches you away from the wall. A teammate added coyote time (a short grace window after leaving the wall) to make it feel fair.
- **Created all the pixel art and animation:** idle, walk, jump, wall slide, crawl, enter platform, exit platform, respawn (waffle press), death by fire, death by falling, and the fire hazard.

**Where to look in the code:**
[`platform.c`](GameTest/GameTest/platform.c) / [`platform.h`](GameTest/GameTest/platform.h) (platforms, crawling and player movement) ·
[`game.c`](GameTest/GameTest/game.c) (core game loop) ·
[`Level1.c`](GameTest/GameTest/Level1.c) (first level, used as the template for the others)

## Development notes

**Problem:** the player had to move freely *inside* platforms that were also solid from the outside.

**What we tried first:** inverting the collision response while the player was inside a platform. It quickly got complicated and fragile.

**What worked:** making platforms hollow outlines rather than solid boxes. The inside is just empty space, so ordinary collision works both inside and outside, and the only special case left is moving the player through the wall on enter and exit. It's the simplest version, and it held up across all 5 levels.

## Controls

| Action | Key |
|---|---|
| Move | `W` `A` `S` `D` |
| Jump | `Space` |
| Wall slide | Hold `A` / `D` against a wall |
| Enter / exit crawl mode (on top of a yellow platform) | `E` |
| Move camera | Mouse to screen edge |
| Reset camera | `R` |
| Pause | `Esc` |
| Skip splash screen | `Esc` |
| Level select | `1`–`5` |

**Debug keys** (left in for testing): `K` restarts the waffle, `P` clears the current level.

## Building from source

**Requirements:** Windows, Visual Studio

1. Clone the repo.
2. Open `GameTest.sln` in Visual Studio.
3. Build and run (`F5`).

CProcessing, the DigiPen graphics library the game is built on, is in the `Extern` folder.

## Team

As a first-year team still learning the ropes, all five of us helped each other across programming, design and testing. Each of us also owned a main area.

| Name | Main contributions |
|---|---|
| Tan Jun Quan | Team lead, platform crawling, wall jump, pixel art and animation |
| Koe Yun Ji | Camera |
| Manfred Sim | Serialization (saving and loading data) |
| Muhammad Raziq | Hazards |
| Muhammad Ashfer | Wall-jump coyote time |

## License

Student project created at DigiPen Institute of Technology Singapore / Singapore Institute of Technology.
All content © 2024 DigiPen (USA), LLC. All rights reserved. Shared for portfolio purposes only.
