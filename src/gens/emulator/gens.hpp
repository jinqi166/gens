#ifndef GENS_HPP
#define GENS_HPP

// GENS version information
#define GENS_APPNAME "Gens"

// Maximum path name length.
// TODO: Use PATH_MAX instead?
#define GENS_PATH_MAX 1024

//#define CLOCK_NTSC 53700000			// More accurate for division round
//#define CLOCK_PAL  53200000

#define CLOCK_NTSC 53693175
#define CLOCK_PAL  53203424

/**
 * STUB: Indicates that this function is a stub.
 */
#define STUB fprintf(stderr, "TODO: STUB: %s()\n", __func__);

/**
 * SET_VISIBLE_LINES: Sets the number of visible lines, depending on CPU mode and VDP setting.
 * If PAL and some VDP register are set, use 240 lines.
 * Otherwise, only 224 lines are visible.
 */
#define SET_VISIBLE_LINES			\
{						\
	if ((CPU_Mode) && (VDP_Reg.Set2 & 0x8))	\
		VDP_Num_Vis_Lines = 240;	\
	else					\
		VDP_Num_Vis_Lines = 224;	\
}

/**
 * Z80_EXEC(): Z80 execution macro.
 * @param cyclesSubtract Cycles to subtract from Cycles_Z80.
 */
#define Z80_EXEC(cyclesSubtract)					\
{									\
	if (Z80_State == 3)						\
		z80_Exec(&M_Z80, Cycles_Z80 - (cyclesSubtract));	\
	else								\
		mdZ80_set_odo(&M_Z80, Cycles_Z80 - (cyclesSubtract));	\
}

#ifdef __cplusplus
extern "C" {
#endif

extern int Debug;
extern int Frame_Skip;
extern int Frame_Number;
extern int DAC_Improv;

void Init_Tab(void);
void Check_Country_Order(void);

void Set_Clock_Freq(const int system);

#ifdef __cplusplus
}
#endif

#endif /* GENS_HPP */
