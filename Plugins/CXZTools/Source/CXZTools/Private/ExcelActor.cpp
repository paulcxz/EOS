#include "ExcelActor.h"
#include "CXZTools.h"
#include "Modules/ModuleManager.h"

AExcelActor::AExcelActor()
{
	m_pBook = NULL;
	m_nSheetCount = 0;
	m_nCurSheet = -1;
	m_pCurFormat = NULL;
}

AExcelActor::~AExcelActor()
{
}

void AExcelActor::BeginPlay()
{
	Super::BeginPlay();
	m_pBook = xlCreateBook();
	if(m_pBook)
	{
		m_pBook->setKey(L"Halil Kural",L"windows-2723210a07c4e90162b26966a8jcdboe");
		if(AddSheet(L"Sheet1"))
		{
			if(SetCurSheet(0))
			{
				return;
			}
		}
	}

	Destroy();
}

void AExcelActor::BeginDestroy()
{
	if(m_pBook)
		m_pBook->release();

	Super::BeginDestroy();
}
bool AExcelActor::AddSheet(const FString& Name)
{
	if (m_pBook)
	{
		Sheet* sheet = m_pBook->addSheet(*Name);
		if (sheet)
		{
			return true;
		}
	}
	return false;
}

bool AExcelActor::Open(const FString& PathName)
{
	if(m_pBook)
	{
		if(m_pBook->load(*PathName))
		{
			if(SetCurSheet(0))
			{
				return true;
			}
		}
	}
	return false;
}

bool AExcelActor::SetCurSheet(int idx)
{
	if (m_pBook)
	{
		Sheet* sheet = m_pBook->getSheet(idx);
		if (sheet)
		{
			m_nCurSheet = idx;
			return true;
		}
	}
	return false;
}

bool AExcelActor::Read(int Row,int Col,FString& Str)
{
	if(m_pBook)
	{
		Sheet* sheet = m_pBook->getSheet(m_nCurSheet);
		if(sheet)
		{
			Str = sheet->readStr(Row,Col);
			return true;
		}
	}
	return false;
}

bool AExcelActor::DelSheet(int idx)
{
	if (m_pBook)
	{
		return m_pBook->delSheet(idx);
	}
	return false;
}

bool AExcelActor::SetFormat(const FExcelToolFormat NewFormat,bool UseDefaultFormat)
{
	if(m_pBook)
	{
		if(UseDefaultFormat)
		{
			m_pCurFormat = NULL;
			return true;
		}
		FCXZToolsModule& cxztool = FModuleManager::LoadModuleChecked<FCXZToolsModule>("CXZTools");
		m_pCurFormat = cxztool.TranslateFormat(m_pBook,NewFormat);
		return true;
	}
	return false;
}

bool AExcelActor::Write(int row, int col, FString str)
{
	if (m_pBook)
	{
		Sheet* sheet = m_pBook->getSheet(m_nCurSheet);
		if (sheet)
		{
			if(m_pCurFormat)
				sheet->writeStr(row,col,*str,m_pCurFormat);
			else
				sheet->writeStr(row,col,*str);
			return true;
		}
	}
	return false;
}

bool AExcelActor::Save(const FString& PathName)
{
	if (m_pBook)
	{
		return m_pBook->save(*PathName);
	}
	return false;
}

bool AExcelActor::AutoFixArea(int rowFirst,int colFirst,int rowLast,int colLast)
{
	if(m_pBook)
	{
		Sheet* sheet = m_pBook->getSheet(m_nCurSheet);
		if(sheet)
		{
			sheet->setAutoFitArea(rowFirst,colFirst,rowLast,colLast);
			return true;
		}
	}
	return false;
}

//bool AExcelActor::CXZSaveExcel(const FString& PathName, const TArray<FExcelLine>& Content)
//{
//	bool ret = false;
//	Book* book = xlCreateBook();
//	if (book)
//	{
//		book->setKey(L"Halil Kural", L"windows-2723210a07c4e90162b26966a8jcdboe");
//		Sheet* sheet = book->addSheet(L"Sheet1");
//		if (sheet)
//		{
//
//			int x, y;
//			x = 0;
//			for (auto itLine : Content)
//			{
//				y = 0;
//				for (auto itCell : itLine.cells)
//				{
//
//					//Format* format = sheet->cellFormat(x, y);
//					//format->setBorderColor(libxl::Color::COLOR_BLUE);
//					//format->patternBackgroundColor();
//					//format->setFillPattern()
//					//format->setFillPattern(libxl::FillPattern::FILLPATTERN_SOLID);
//					//format->setPatternForegroundColor(libxl::Color::COLOR_RED);
//					Format* format = book->addFormat();
//					if (x == 0)
//					{
//						format->setFillPattern(libxl::FillPattern::FILLPATTERN_SOLID);
//						format->setPatternForegroundColor(libxl::Color::COLOR_BRIGHTGREEN);
//						format->setBorder(libxl::BORDERSTYLE_MEDIUM);
//						format->setAlignH(libxl::ALIGNH_CENTER);
//						format->setAlignV(libxl::ALIGNV_CENTER);
//						libxl::Font* font = book->addFont();
//						font->setBold(true);
//						font->setSize(16);
//						format->setFont(font);
//					}
//					else
//					{
//						format->setBorder(libxl::BORDERSTYLE_THIN);
//					}
//					sheet->writeStr(x, y, *itCell, format);
//
//					y++;
//				}
//				x++;
//			}
//			/*sheet->writeStr(2, 1, L"Hello, World !");
//			sheet->writeNum(4, 1, 1000);
//			sheet->writeNum(5, 1, 2000);
//
//			Font* font = book->addFont();
//			font->setColor(libxl::Color::COLOR_RED);
//			font->setBold(true);
//			Format* boldFormat = book->addFormat();
//			boldFormat->setFont(font);
//			sheet->writeFormula(6, 1, L"SUM(B5:B6)", boldFormat);
//
//			Format* dateFormat = book->addFormat();
//			dateFormat->setNumFormat(NUMFORMAT_DATE);
//			sheet->writeNum(8, 1, book->datePack(2008, 4, 29), dateFormat);
//
//			sheet->setCol(1, 1, 12);*/
//
//			sheet->setAutoFitArea();
//			if (book->save(*PathName))
//			{
//				ret = true;
//			}
//		}
//		book->release();
//	}
//	return ret;
//}