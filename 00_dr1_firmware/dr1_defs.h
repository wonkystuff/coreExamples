#define WTSIZE   (512L)

extern const uint8_t  sine[WTSIZE];
extern const uint8_t  ramp[WTSIZE];
extern const uint8_t  sq[WTSIZE];
extern const uint8_t  triangle[WTSIZE];

// The knobs onthe standalone Core1 are swapped compared to the
// AEModular version, so we try for a consistent 'user experience'
#if defined AECORE
#define MAINKNOB                        (3)
#define SECONDARYKNOB                   (2)
#elif defined CORE1D
#define MAINKNOB                        (2)
#define SECONDARYKNOB                   (3)
#else
#error Board type not defined!
#endif
