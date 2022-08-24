#pragma once
#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "enum.h"
#include "libxl.h"
#include "Structs.generated.h"

using namespace libxl;
USTRUCT(BlueprintType)
struct FExcelLine
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Excel Tool")
	TArray<FString> cells;

public:
	FExcelLine()
	{

	}
};

UENUM(BlueprintType)
enum class EExcelToolColor : uint8
{
	ENTRY				=	0,
	BLACK				=	libxl::COLOR_BLACK,
	WHITE				=	libxl::COLOR_WHITE,
	RED					=	libxl::COLOR_RED,
	BRIGHTGREEN			=	libxl::COLOR_BRIGHTGREEN,
	BLUE				=	libxl::COLOR_BLUE,
	YELLOW				=	libxl::COLOR_YELLOW,
	PINK				=	libxl::COLOR_PINK,
	TURQUOISE			=	libxl::COLOR_TURQUOISE,
	DARKRED				=	libxl::COLOR_DARKRED,
	GREEN				=	libxl::COLOR_GREEN,
	DARKBLUE			=	libxl::COLOR_DARKBLUE,
	DARKYELLOW			=	libxl::COLOR_DARKYELLOW,
	VIOLET				=	libxl::COLOR_VIOLET,
	TEAL				=	libxl::COLOR_TEAL,
	GRAY25				=	libxl::COLOR_GRAY25,
	GRAY50				=	libxl::COLOR_GRAY50,
	PERIWINKLE_CF		=	libxl::COLOR_PERIWINKLE_CF,
	PLUM_CF				=	libxl::COLOR_PLUM_CF,
	IVORY_CF			=	libxl::COLOR_IVORY_CF,
	LIGHTTURQUOISE_CF	=	libxl::COLOR_LIGHTTURQUOISE_CF,
	DARKPURPLE_CF		=	libxl::COLOR_DARKPURPLE_CF,
	CORAL_CF			=	libxl::COLOR_CORAL_CF,
	OCEANBLUE_CF		=	libxl::COLOR_OCEANBLUE_CF,
	ICEBLUE_CF			=	libxl::COLOR_ICEBLUE_CF,
	DARKBLUE_CL			=	libxl::COLOR_DARKBLUE_CL,
	PINK_CL				=	libxl::COLOR_PINK_CL,
	YELLOW_CL			=	libxl::COLOR_YELLOW_CL,
	TURQUOISE_CL		=	libxl::COLOR_TURQUOISE_CL,
	VIOLET_CL			=	libxl::COLOR_VIOLET_CL,
	DARKRED_CL			=	libxl::COLOR_DARKRED_CL,
	TEAL_CL				=	libxl::COLOR_TEAL_CL,
	BLUE_CL				=	libxl::COLOR_BLUE_CL,
	SKYBLUE				=	libxl::COLOR_SKYBLUE,
	LIGHTTURQUOISE		=	libxl::COLOR_LIGHTTURQUOISE,
	LIGHTGREEN			=	libxl::COLOR_LIGHTGREEN,
	LIGHTYELLOW			=	libxl::COLOR_LIGHTYELLOW,
	PALEBLUE			=	libxl::COLOR_PALEBLUE,
	ROSE				=	libxl::COLOR_ROSE,
	LAVENDER			=	libxl::COLOR_LAVENDER,
	TAN					=	libxl::COLOR_TAN,
	LIGHTBLUE			=	libxl::COLOR_LIGHTBLUE,
	AQUA				=	libxl::COLOR_AQUA,
	LIME				=	libxl::COLOR_LIME,
	GOLD				=	libxl::COLOR_GOLD,
	LIGHTORANGE			=	libxl::COLOR_LIGHTORANGE,
	ORANGE				=	libxl::COLOR_ORANGE,
	BLUEGRAY			=	libxl::COLOR_BLUEGRAY,
	GRAY40				=	libxl::COLOR_GRAY40,
	DARKTEAL			=	libxl::COLOR_DARKTEAL,
	SEAGREEN			=	libxl::COLOR_SEAGREEN,
	DARKGREEN			=	libxl::COLOR_DARKGREEN,
	OLIVEGREEN			=	libxl::COLOR_OLIVEGREEN,
	BROWN				=	libxl::COLOR_BROWN,
	PLUM				=	libxl::COLOR_PLUM,
	INDIGO				=	libxl::COLOR_INDIGO,
	GRAY80				=	libxl::COLOR_GRAY80,
	DEFAULT_FOREGROUND	=	libxl::COLOR_DEFAULT_FOREGROUND,
	DEFAULT_BACKGROUND	=	libxl::COLOR_DEFAULT_BACKGROUND,
	TOOLTIP				=	libxl::COLOR_TOOLTIP,
	//ETC_COLOR_AUTO					=	libxl::COLOR_AUTO
};

UENUM(BlueprintType)
enum class EExcelToolBorderStyle : uint8
{
	ENTRY				= 0,
	NONE				= libxl::BORDERSTYLE_NONE,
	THIN				= libxl::BORDERSTYLE_THIN,
	MEDIUM				= libxl::BORDERSTYLE_MEDIUM,
	DASHED				= libxl::BORDERSTYLE_DASHED,
	DOTTED				= libxl::BORDERSTYLE_DOTTED,
	THICK				= libxl::BORDERSTYLE_THICK,
	DOUBLE				= libxl::BORDERSTYLE_DOUBLE,
	HAIR				= libxl::BORDERSTYLE_HAIR,
	MEDIUMDASHED		= libxl::BORDERSTYLE_MEDIUMDASHED,
	DASHDOT				= libxl::BORDERSTYLE_DASHDOT,
	MEDIUMDASHDOT		= libxl::BORDERSTYLE_MEDIUMDASHDOT,
	DASHDOTDOT			= libxl::BORDERSTYLE_DASHDOTDOT,
	MEDIUMDASHDOTDOT	= libxl::BORDERSTYLE_MEDIUMDASHDOTDOT,
	SLANTDASHDOT		= libxl::BORDERSTYLE_SLANTDASHDOT,
};

UENUM(BlueprintType)
enum class EExcelToolAlignH: uint8
{
	ENTRY		= 0,
	GENERAL		= libxl::ALIGNH_GENERAL,
	LEFT		= libxl::ALIGNH_LEFT,
	CENTER		= libxl::ALIGNH_CENTER,
	RIGHT		= libxl::ALIGNH_RIGHT,
	FILL		= libxl::ALIGNH_FILL,
	JUSTIFY		= libxl::ALIGNH_JUSTIFY,
	MERGE		= libxl::ALIGNH_MERGE,
	DISTRIBUTED	= libxl::ALIGNH_DISTRIBUTED,
};

UENUM(BlueprintType)
enum class EExcelToolAlignV: uint8
{
	ENTRY		= 0,
	TOP			= libxl::ALIGNV_TOP,
	CENTER		= libxl::ALIGNV_CENTER,
	BOTTOM		= libxl::ALIGNV_BOTTOM,
	JUSTIFY		= libxl::ALIGNV_JUSTIFY,
	DISTRIBUTED	= libxl::ALIGNV_DISTRIBUTED,
};


USTRUCT(BlueprintType)
struct FExcelToolFormat
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Excel Tool")
		bool FontBold;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Excel Tool")
		int32 FontSize;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Excel Tool")
		EExcelToolColor FontColor;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Excel Tool")
		EExcelToolColor BGColor;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Excel Tool")
		EExcelToolAlignH AlignH;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Excel Tool")
		EExcelToolAlignV AlignV;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Excel Tool")
		EExcelToolBorderStyle BorderStyle;


public:
	FExcelToolFormat():
		FontBold(false),
		FontSize(11),
		FontColor(EExcelToolColor::ENTRY),
		BGColor(EExcelToolColor::ENTRY),
		AlignH(EExcelToolAlignH::ENTRY),
		AlignV(EExcelToolAlignV::ENTRY),
		BorderStyle(EExcelToolBorderStyle::ENTRY)
	{

	}
};