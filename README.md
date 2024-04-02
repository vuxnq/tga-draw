## drawing tga image

this program draws user's input into a [tga](https://en.wikipedia.org/wiki/Truevision_TGA) image

## usage

### build

```sh
# clone the repository
$ git clone https://github.com/vuxnq/---.git
$ cd ---

# build
$ make

# build and run with with test inputs
$ make input1 rm
$ make input2 rm
```

### run

```sh
./program --output <filepath.tga> --width <number> --height <number>
```

### arguments

- `--output <file-path>` - output file path
- `--width <number>` - width of an image
- `--height <number>` - height of an image

**_every argument must be included when running a program_**

### shapes

- `line x1,y1,x2,y2,r,g,b,a`

  - (**x1**, **y1**) - starting point
  - (**x2**, **y2**) - end point
  - (**r**, **g**, **b**, **a**) - [colour](#colour)

- `circle x,y,p,r,g,b,a`

  - (**x**, **y**) - centre of a circle
  - **p** - radius
  - (**r**, **g**, **b**, **a**) - [colour](#colour)

- `triangle x,y,s,r,g,b,a`

  - (**x**, **y**) - centre of a triangle
  - **s** - side length of a triangle
  - (**r**, **g**, **b**, **a**) - [colour](#colour)

- `rectangle x,y,w,h,r,g,b,a`

  - (**x**, **y**) - top-left corner of a rectangle
  - **w** - width of a rectangle
  - **h** - height of a rectangle
  - (**r**, **g**, **b**, **a**) - [colour](#colour)

- `rotated-rectangle angle,x,y,width,height,r,g,b,a`
  - **angle** - angle in degrees
  - (**x**, **y**) - centre of a rotated rectangle
  - **w** - width of a rectangle
  - **h** - height of a rectangle
  - (**r**, **g**, **b**, **a**) - [colour](#colour)
- `save` - saves current version of image into an [--output](#arguments) file
- `exit` - saves and exits the program

### colour

- **r** - red
- **g** - green
- **b** - blue
- **a** - alpha (opacity)

all values must be in range of **0** (0%) to **255** (100%)

**example:** (255, 0, 0, 255) is displayed as red, because red is set to its highest value (255) and the others are set to 0
