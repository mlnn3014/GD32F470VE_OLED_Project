# Codex Project Instructions

## Engineering Preferences

- Keep code simple, direct, and easy to continue programming against. Do not add abstraction unless it clearly reduces real complexity.
- Prefer short, readable names over overly formal names. Names should be clear but not awkward.
- Make changes in small, focused steps and preserve existing behavior unless the task explicitly asks for behavior changes.
- After changing source layout or adding files, update the Keil project include paths and source file references.
- Keep VSCode EIDE configuration in sync with Keil when changing include paths, source paths, or project structure.
- Run or request Keil build verification when possible. Treat unrelated existing build errors separately from the current task.

## BSP Style

- BSP modules should isolate hardware details while exposing simple interfaces.
- Store BSP headers in `Bsp/Inc` and BSP source files in `Bsp/Src`.
- Prefer GD32 standard peripheral library calls over control-style macros for hardware operations.
- Avoid public hardware-control macros such as `LED1_SET` or `LED_WRITE`; use functions instead.

## LED Rules

- Board LEDs are active-high: GPIO `SET` turns an LED on, GPIO `RESET` turns it off.
- Keep the LED API simple and convenient for application code:
  - `led_init()`
  - `led_on(LED_1)`
  - `led_off(LED_1)`
  - `led_set(LED_1, 1U)`
  - `led_toggle(LED_1)`
- Use simple LED identifiers: `LED_1`, `LED_2`, `LED_3`, `LED_4`, `LED_5`, `LED_6`, `LED_COUNT`.
- LED app logic should stay straightforward. Avoid unnecessary state masks, cache layers, or extra wrapper functions unless there is a clear need.
