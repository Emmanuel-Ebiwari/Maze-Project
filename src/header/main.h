#ifndef MAIN_H
#define MAIN_H

#include <SDL2/SDL.h>
#include <math.h>


/* ========================================================== */
/* ========================================================== */
/* ========================================================== */
/* ========================================================== */
/* Config */
/* Special settings */
#define ONLY_NORMALIZED 1
#define ONLY_FIRST_HIT 2
extern char slowRenderMode;
extern char rayCastMode;

/* Misc. constants */
#define FALSE 0
#define TRUE  1
#define PI    3.14159265358979323846 /* C89 does not seem to define this constant */
#define EPS   0.00000001

/* Floating point operations */
#define MAKE_FLOAT_NONZERO(A)  ((fabs((A)) < EPS) ? EPS : A) /* Make any value less than epsilon equal to epsilon */

/* Window parameters*/
#define WINDOW_WIDTH  640
#define WINDOW_HEIGHT 480

/* Raycaster parameters */
#define TEXTURE_SIZE           64
#define WALL_SIZE              64
#define HUD_MAP_SIZE           WINDOW_HEIGHT
#define FOV                    (PI / 3.0f)               /* 60 degrees */
#define PLAYER_MOVEMENT_SPEED  5.0f
#define PLAYER_ROT_SPEED       ((3.0f * (PI)) / 180.0f)  /* 3 degrees per frame */
#define PLAYER_SIZE            20

/* Projection parameters */
#define VIEWPLANE_LENGTH  WINDOW_WIDTH
#define VIEWPLANE_DIR_X  -1
#define VIEWPLANE_DIR_Y   0
#define PLAYER_DIR_X      0     /* Player direction must be perpendicular to viewplane */
#define PLAYER_DIR_Y      1
#define PLAYER_START_X    (2.5f * WALL_SIZE)
#define PLAYER_START_Y    (2.5f * WALL_SIZE)

/* Map constants */
#define MAP_GRID_WIDTH    10
#define MAP_GRID_HEIGHT   10
#define MAP_PIXEL_WIDTH   (MAP_GRID_WIDTH * WALL_SIZE)
#define MAP_PIXEL_HEIGHT  (MAP_GRID_HEIGHT * WALL_SIZE)

/* Map wall types */
#define P            -1  /* Player start */
#define R             1  /* Red wall */
#define G             2  /* Green wall */
#define B             3  /* Blue wall */
#define W             4  /* Gray wall */

#define CEILING_COLOR  RGBtoABGR(0x65, 0x65, 0x65)
#define FLOOR_COLOR    RGBtoABGR(0xAA, 0xAA, 0xAA)


/* Globals */
extern const short MAP[MAP_GRID_HEIGHT][MAP_GRID_WIDTH];
extern char distortion;
extern char textureMode;
extern Uint32* screenBuffer;
extern const Uint32 COLORS[];
extern Uint32* TEXTURES[];

/* Config */
/* ========================================================== */
/* ========================================================== */
/* ========================================================== */
/* ========================================================== */


/* ========================================================== */
/* ========================================================== */
/* ========================================================== */
/* ========================================================== */
/* Gfx */

/**
 * Macro to convert from RGB color components to an ABGR integer
 */
#define RGBtoABGR(R,G,B)   (0xFF000000 | ((B) << 16) | ((G) << 8) | (R))


/*========================================================
 * Library debug functions
 *========================================================
 */

/* Get a string describing the last error encountered by this library */
const char* gfxGetError();


/*========================================================
 * GFX management functions
 *========================================================
 */


/**
 * Initialize the graphics environment
 *
 * title:  The title to use for the displayed window
 * width:  The width of the displayed window in pixels
 * height: The height of the displayed window in pixels
 */
int initGFX(char* title, unsigned int width, unsigned int height);

/**
 * Create a texture buffer
 *
 * width:  The width of the texture buffer
 * height: The height of the texture buffer
 *
 * Returns: A pointer to the texture pixel buffer
 */
void* createTexture(unsigned int width, unsigned int height);

/**
 * Free a texture buffer from memory
 *
 * texture: A pointer to the texture to be destroyed
 *
 * Returns: 1 if the operation was successful, 0 otherwise.
 */
int destroyTexture(void* texture);

/**
 * Draw a texture to the window's entire rendering area.
 *
 * texture: A pointer to the texture to be drawm
 *
 * Returns: 1 if the operation was successful, 0 otherwise.
 */
void displayFullscreenTexture(void* texture);

/**
 * Terminate the graphics environment and free all allocated resources
 */
void destroyGFX();


/*========================================================
 * Drawing functions
 *========================================================
 */

/**
 * Set the current drawing color for primitives
 *
 * r: The red channel of the color
 * g: The green channel of the color
 * b: The blue channel of the color
 * a: The alpha (blending) channel of the color
 */
void setDrawColor(int r, int g, int b, int a);

/**
 * Draw a line between two points on the screen
 *
 * x1: The starting point's x component
 * y1: The starting point's y component
 * x2: The finishing point's x component
 * y2: The finishing point's y component
 */
void drawLine(int x1, int y1, int x2, int y2);

/**
 * Draw a filled rectangle to the screen
 *
 * x: The x component of the top-left corner of the rectangle
 * y: The y component of the top-left corner of the rectangle
 * w: The width of the rectangle
 * h: The height of the rectangle
 */
void fillRect(int x, int y, int w, int h);

/**
 * Draw the outline of a rectangle to the screen
 *
 * x: The x component of the top-left corner of the rectangle
 * y: The y component of the top-left corner of the rectangle
 * w: The width of the rectangle
 * h: The height of the rectangle
 */
void drawRect(int x, int y, int w, int h);

/**
 * Refresh the primitive objects on the screen
 */
void presentRenderer();

/**
 * Clear the primitive objects on the screen
 */
void clearRenderer();


/*========================================================
 * Utility functions
 *========================================================
 */

/**
 * Generate an xor square texture
 *
 * size:      The size of the square texture in pixels
 * redmask:   The bitwise mask used on the red channel when picking colors to use
 * greenmask: The bitwise mask used on the green channel when picking colors to use
 * bluemask:  The bitwise mask used on the blue channel when picking colors to use
 *
 * Returns: A pointer to the generated texture
 */
Uint32* generateXorTexture(int size, int redmask, int greenmask, int bluemask);

/**
 * Generate a red xor square texture
 *
 * size: The size of the square texture in pixels
 *
 * Returns: A pointer to the generated texture
 */
Uint32* generateRedXorTexture(int size);

/**
 * Generate a green xor square texture
 *
 * size: The size of the square texture in pixels
 *
 * Returns: A pointer to the generated texture
 */
Uint32* generateGreenXorTexture(int size);

/**
 * Generate a blue xor square texture
 *
 * size: The size of the square texture in pixels
 *
 * Returns: A pointer to the generated texture
 */
Uint32* generateBlueXorTexture(int size);

/**
 * Generate a gray xor square texture
 *
 * size: The size of the square texture in pixels
 *
 * Returns: A pointer to the generated texture
 */
Uint32* generateGrayXorTexture(int size);

/* Gfx */
/* ========================================================== */
/* ========================================================== */
/* ========================================================== */
/* ========================================================== */

/* ========================================================== */
/* ========================================================== */
/* ========================================================== */
/* ========================================================== */
/* linalg */

#define MIN(A, B)      ((A) < (B) ? (A) : (B))
#define MAX(A, B)      ((A) > (B) ? (A) : (B))

/* A 3D identity matrix */
#define IDENTITY_M     {{1,0,0},{0,1,0},{0,0,1}}

/* A 2D homogeneous matrix */
#define HOMOGENEOUS_V3 {0, 0, 1}

/* Types */
typedef struct {
    float x;
    float y;
    float z;
} Vector3f;

typedef float Matrix3f[3][3];

/**
 * Add two 2D homogeneous vectors.
 * Since the output is homogeneous, its z component
 * is fixed to '1'.
 *
 * vec1: The first vector.
 * vec2: The second vector.
 *
 * Returns: The addition of vec1 and vec2.
 */
Vector3f vectorAdd(Vector3f* vec1, Vector3f* vec2);

/**
 * Subtract one 2D homogeneous vector from another.
 * Since the output is homogeneous, its z component
 * is fixed to '1'.
 *
 * vec1: The first vector.
 * vec2: The second vector.
 *
 * Returns: The subtraction of vec2 from vec1 (vec1 - vec2).
 */
Vector3f vectorSubtract(Vector3f* vec1, Vector3f* vec2);

/**
 * Scale a homogeneous 2D vector by a scalar.
 * Since the output is homogeneous, its z component
 * is fixed to '1'.
 *
 * vec:    The vector to scale.
 * scalar: The scalar to use.
 *
 * Returns: The scaled vector.
 */
Vector3f homogeneousVectorScale(Vector3f* vec, float scalar);

/**
 * Normalize a homogeneous 2D vector (set its length to 1)
 * Since the output is homogeneous, its z component
 * is fixed to '1'.
 *
 * vec: The vector to normalize.
 *
 * Returns: The normalized vector.
 */
Vector3f normalizeVector(Vector3f* vec);

/**
 * Project a 2D vector onto another.
 * Since the output is homogeneous, its z component
 * is fixed to '1'.
 *
 * vec1: The vector to project.
 * vec2: The vector to project on to.
 *
 * Returns: The projected vector.
 */
Vector3f vectorProjection(Vector3f* vec1, Vector3f* vec2);

/**
 * Get the magnitude of a homogeneous 2D vector.
 *
 * vec: The vector to find the magnitude of.
 *
 * Returns: The magnitude (length) of the vector.
 */
float homogeneousVectorMagnitude(Vector3f* vec);

/**
 * Find the dot product of two homogeneous 2D vectors.
 *
 * vec1: The first vector.
 * vec2: The second vector.
 *
 * Returns: Dot product of the first and second vectors.
 */
float vectorDotProduct(Vector3f* vec1, Vector3f* vec2);

/**
 * Multiply a 3D vector by a 3D square matrix.
 *
 * mat: The transformation matrix.
 * vec: The vector to be multiplied.
 */
void matrixVectorMultiply(Matrix3f* mat, Vector3f* vec);

/**
 * Multiply a matrix by another matrix.
 * The first matrix will hold the result.
 *
 * mat1: The first matrix.
 * mat2: The second matrix.
 */
void matrixMatrixMultiply(Matrix3f* mat1, Matrix3f* mat2);

/**
 * Copy the values of one matrix into another.
 *
 * dst: The destination matrix.
 * src: The source matrix.
 */
void matrix3fCopy(Matrix3f* dst, Matrix3f* src);

/* linalg */
/* ========================================================== */
/* ========================================================== */
/* ========================================================== */
/* ========================================================== */

/* ========================================================== */
/* ========================================================== */
/* ========================================================== */
/* ========================================================== */
/* map */

/**
 * Render the overhead map to the screen.
 */
void renderOverheadMap();

/* map */
/* ========================================================== */
/* ========================================================== */
/* ========================================================== */
/* ========================================================== */

/* ========================================================== */
/* ========================================================== */
/* ========================================================== */
/* ========================================================== */
/* player */

/* Global data */
extern Vector3f playerPos;
extern Vector3f playerDir;

/* Global toggles */
extern char movingForward;
extern char movingBack;
extern char turningLeft;
extern char turningRight;
extern char playerIsRunning;

/* Functions */

/**
 * Initialize the player.
 */
void initPlayer();

/**
 * Update the player for the current frame.
 */
void updatePlayer();

/**
 * Move the player by a given movement vector.
 *
 * dx: The x component of the movement vector.
 * dy: The y component of the movement vector.
 */
void movePlayer(float dx, float dy);

/**
 * Check if a given movement vector intersects with the world
 * and should be clipped.
 *
 * dx: The x component of the movement vector to check.
 * dy: The y component of the movement vector to check.
 *
 * Returns: Zero if the vector should not be clipped, non-zero otherwise.
 */
int clipMovement(float dx, float dy);

/* player */
/* ========================================================== */
/* ========================================================== */
/* ========================================================== */
/* ========================================================== */

/* ========================================================== */
/* ========================================================== */
/* ========================================================== */
/* ========================================================== */
/* raycaster */

/* Constants */
#define RAY_EPS   (WALL_SIZE / 3.0f)

/* Datatypes */
typedef struct {
    Vector3f vRay;
    Vector3f hRay;
} RayTuple;

/* Global data */
extern Vector3f viewplaneDir;
extern float distFromViewplane;
extern Matrix3f counterClockwiseRotation;
extern Matrix3f clockwiseRotation;
extern RayTuple rays[VIEWPLANE_LENGTH];

/* Functions */

/**
 * Initialize rays as a set of normalized vectors,
 * all pointing in their appropriate directions.
 */
void initializeRayDirections();

/**
 * Set the length of rays in an array such that
 * they each extend from the player to their first
 * intersection in the world.
 *
 * rays: The input array of rays.
 */
void extendRaysToFirstHit(RayTuple* rays);

/**
 * Find the stepping vector of a ray which will bring it
 * from one vertical world intersection to the next.
 *
 * ray: The ray to find the vertical step vector for.
 *
 * Returns: The vertical step vector.
 */
Vector3f findVerticalRayStepVector(Vector3f* ray);

/**
 * Find the stepping vector of a ray which will bring it
 * from one horizontal world intersection to the next.
 *
 * ray: The ray to find the horizontal step vector for.
 *
 * Returns: The horizontal step vector.
 */
Vector3f findHorizontalRayStepVector(Vector3f* ray);

/**
 * Cast a list of prepared rays into the world.
 *
 * rays: The list of rays to cast.
 */
void raycast(RayTuple* rays);

/**
 * Get the tile coordinate (x, y) for the vertical intersection
 * point of a ray and the world.
 *
 * ray: The ray to find the tile coordinate for.
 *
 * Returns: The vertical intersection tile coordinate for the ray.
 */
Vector3f getTileCoordinateForVerticalRay(Vector3f* ray);

/**
 * Get the tile coordinate (x, y) for the horizontal intersection
 * point of a ray and the world.
 *
 * ray: The ray to find the tile coordinate for.
 *
 * Returns: The horizontal intersection tile coordinate for the ray.
 */
Vector3f getTileCoordinateForHorizontalRay(Vector3f* ray);

/**
 * Update the raycaster (setup and perform raycasting) for
 * the current frame.
 */
void updateRaycaster();

/**
 * Initialize the raycaster.
 */
void initRaycaster();

/* raycaster */
/* ========================================================== */
/* ========================================================== */
/* ========================================================== */
/* ========================================================== */


/* ========================================================== */
/* ========================================================== */
/* ========================================================== */
/* ========================================================== */
/* renderer */

/* Macros */
#define XY_TO_SCREEN_INDEX(X, Y)   (((Y) * WINDOW_WIDTH) + (X))
#define XY_TO_TEXTURE_INDEX(X, Y)   (((Y) * TEXTURE_SIZE) + (X))
#define DARKEN_COLOR(C)     ((((C) >> 1) & 0x7F7F7F7F) | 0xFF000000)

/* Enums */
typedef enum {HORIZONTAL_RAY, VERTICAL_RAY} RayType;

/* Functions */

/**
 * Calculate the draw height of a pixel column for a given
 * ray length.
 *
 * rayLength: The ray length to use.
 *
 * Returns: The pixel height of a vertical column to draw.
 */
float calculateDrawHeight(float rayLength);

/**
 * Draw a textured pixel column on the screen.
 *
 * x:          The x coordinate of the column.
 * wallYStart: The starting y coordinate of the pixel column.
 * length:     The length of the column.
 * textureX:   The texture column number to use for the strip.
 * texture:    The texture to use.
 * darken:     Non-zero if the strip should be darkened, zero otherwise.
 */
void drawTexturedStrip(int x, float wallYStart, float length, int textureX, Uint32* texture, char darken);

/**
 * Draw an un-textured pixel column on the screen.
 *
 * x:          The x coordinate of the column.
 * wallYStart: The starting y coordinate of the pixel column.
 * length:     The length of the column.
 * ABGRColor:  The color (ABGR) to use.
 * darken:     Non-zero if the strip should be darkened, zero otherwise.
 */
void drawUntexturedStrip(int x, float wallYStart, float length, Uint32 ABGRColor, char darken);

/**
 * Find the texture column number to use for a given ray.
 *
 * ray:   The ray to use.
 * rtype: The type of ray intersection (see above definition of RayType)
 *
 * Returns: The texture column number to use.
 */
int getTextureColumnNumberForRay(Vector3f* ray, RayType rtype);

/**
 * Get the barrel-distortion corrected ray length for a given ray.
 *
 * ray: The ray to undistort.
 *
 * Returns: The undistorted length of the ray.
 */
float getUndistortedRayLength(Vector3f* ray);

/**
 * Render the scene.
 * This assumes that rays have already been cast.
 */
void renderProjectedScene();

/* renderer */
/* ========================================================== */
/* ========================================================== */
/* ========================================================== */
/* ========================================================== */

#endif /* MAIN_H */