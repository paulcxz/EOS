#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "structs.h"
#include "libxl.h"
#include "enum.h"
#include "ExcelActor.generated.h"

using namespace libxl;
/**
 *
 */
UCLASS()
class CXZTOOLS_API AExcelActor : public AActor
{
	GENERATED_BODY()

public:
	AExcelActor();
	virtual ~AExcelActor();

	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;
	UFUNCTION(BlueprintCallable,Category = "Excel Tool")
	bool Open(const FString& PathName);

	UFUNCTION(BlueprintPure,Category = "Excel Tool")
	bool Read(int Row,int Col,FString& Str);

	UFUNCTION(BlueprintCallable, Category = "Excel Tool")
	bool Write(int row,int col,FString str);
	
	UFUNCTION(BlueprintCallable, Category = "Excel Tool")
	bool SetFormat(const FExcelToolFormat NewFormat,bool UseDefaultFormat = false);

	UFUNCTION(BlueprintCallable, Category = "Excel Tool")
	bool Save(const FString& PathName);

	UFUNCTION(BlueprintCallable, Category = "Excel Tool")
	bool AddSheet(const FString& Name);

	UFUNCTION(BlueprintCallable, Category = "Excel Tool")
	bool SetCurSheet(int idx);

	UFUNCTION(BlueprintCallable, Category = "Excel Tool")
	bool DelSheet(int idx);

	UFUNCTION(BlueprintCallable,Category = "Excel Tool")
	bool AutoFixArea(int rowFirst = 0,int colFirst = 0,int rowLast = -1,int colLast = -1);

	
private:
	Book* m_pBook;
	Format* m_pCurFormat;
	int m_nSheetCount;
	int m_nCurSheet;
};