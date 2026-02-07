*This project has been created as part of the 42 curriculum by atursun.*

# Fdf

## Description

**FDF (Fil De Fer - Wireframe)** is a fundamental computer graphics project that creates a wireframe model representation of a 3D landscape.

This project is to draw the wireframe model of a given 3D `.fdf` formatted file map on a 2D screen using isometric projection.

### Example

The following map data (representing the number 42):

```text
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
0  0 10 10  0  0 10 10  0  0  0 10 10 10 10 10  0  0  0
0  0 10 10  0  0 10 10  0  0  0  0  0  0  0 10 10  0  0
0  0 10 10  0  0 10 10  0  0  0  0  0  0  0 10 10  0  0
0  0 10 10 10 10 10 10  0  0  0  0 10 10 10 10  0  0  0
0  0  0 10 10 10 10 10  0  0  0 10 10  0  0  0  0  0  0
0  0  0  0  0  0 10 10  0  0  0 10 10  0  0  0  0  0  0
0  0  0  0  0  0 10 10  0  0  0 10 10 10 10 10 10  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
```

Will be rendered as:

![42](https://media.licdn.com/dms/image/v2/D4E22AQF4ty9ok2Seig/feedshare-shrink_1280/feedshare-shrink_1280/0/1711968634652?e=1772064000&v=beta&t=2huxeiUGiqNht7GAtDVacpOCPJLPuO7B5td_RLfwSRA)

**Project Goals:**
- Learn to use the MiniLibX graphics library
- Understand the basics of graphics programming
- Learn how to display points in 3D space from a specific viewpoint
- Apply isometric projection mathematics
- Use Bresenham's line drawing algorithm

---

## Instructions

### Compilation

To compile the project:

```bash
make
```

Cleaning commands:

```bash
make clean
make fclean
```

Rebuild:
```bash
make re  
```

### Execution

The program is run from the command line with a `.fdf` map file:

```bash
./fdf test_map/<map_name>.fdf
```

### Controls
- **ESC** → Close the program
- **X (Window close button)** → Close the program

### Map File Format

The `.fdf` file is a text-based format where each number represents a 3D point:

```
0  0  0  0  0
0 10 10 10  0
0 10  0 10  0
0 10 10 10  0
0  0  0  0  0
```

- **Horizontal position** → X coordinate (column index)
- **Vertical position** → Y coordinate (row index)
- **Number value** → Z coordinate (height/altitude)
- **(Optional) Color** → Hexadecimal color code in format `10,0xFF0000`

---

## Resources

- [MiniLibX Documentation](https://harm-smits.github.io/42docs/libs/minilibx)
- [Bresenham's Line Algorithm](https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm)
- [Isometric Projection](https://en.wikipedia.org/wiki/Isometric_projection)

### AI Usage

AI tools were used only for concept clarification, understanding isometric projection mathematics, guidance during debugging, and drafting the README.md No project code was generated or modified by AI.
