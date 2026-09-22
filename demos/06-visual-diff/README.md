# Demo 06 — visual diff

Goal: detect differences between images.

Prompt:

```text
Show the difference between the reference image [Image 1] and the tested image [Image 2]. Do not compare exact values, only whether they are completely absent or zero. Focus on missing components or their displacement.
```

## Setup

Place the reference image and the tested image in this directory (for example, `reference.png` and `tested.png`).

Run the diff using the tool or script configured for this demo.

## Example output to look for

- Components present in the reference image but missing from the tested image, or vice versa.
- Components that have shifted position significantly.
- Regions where a value is absent or zero instead of the expected content.

## Debrief

Visual diff is useful for catching layout regressions or missing UI elements without asserting on exact pixel values or content. The focus should be on structural changes, not minor rendering variations.