#include <string>
#include <vector>
#include "gtest/gtest.h"

#include "../ruleengine/Constant_sbx.h"
#include "../ruleengine/KonceptInfo_sbx.h"
#include "../ruleengine/ProductElementValue_sbx.h"
#include "../ruleengine/RuleConstantContainer_sbx.h"
#include "../ruleengine/RuleEngine_sbx.h"
#include "../ruleengine/RuleCatalogue.h"
#include "../ruleengine/Rule.h"
#include "../ruleengine/sbxTypes.h"
#include "../ruleengine/TA_sbx.h"
#include "../ruleengine/ValidationResult.h"

#include "ruleenginetestutils.h"

using namespace std;
using namespace sbx;

class RuleEngine_CONTEXT_KI_OSV_25_50 : public ::testing::Test  {
protected:
    virtual void SetUp() {
        re = RuleEngine();
        re.initConstants(get_file_contents("basedata-ruleconstants.json"));
        re.parseRuleCatalogueJSON(get_file_contents("rule-catalogue.json"));

        KonceptInfo ki {17, // UnderkonceptOid:OSV 25-49
        	{ {11, "true"}, // Parameter-Basis
        	  {1, "true"}, // Solidarisk faellestarif
			  {6, "true"} // SEB Firmapensionspulje
        	} };
        re.initContext(ki);
    }

    RuleEngine re;
};


// Test Opsparingsprodukter - PE(72, 73, 74, 75, 201)-P(60)
// Allowed values: true false
TEST_F(RuleEngine_CONTEXT_KI_OSV_25_50, Opsparingsprodukt_ALL_SELECTED_POSITIVE) {
	TA ta { "15124040", 4}; // KonceptOid 4 - OSV
	ta.setValue(kMarkedspension_MK, true )
			.setValue(kTraditionel_MK, true)
			.setValue(kTidspensionMedGaranti_MK, true)
			.setValue(kTidspensionUdenGaranti_MK, true)
			.setValue(kLink_MK, true);

	auto r = re.validate(ta, {kMarkedspension_MK, kTraditionel_MK, kTidspensionMedGaranti_MK, kTidspensionUdenGaranti_MK, kLink_MK} );
	EXPECT_TRUE(r.isAllOk());
}

// Test Opsparingsprodukter - PE(72, 73, 74, 75, 201)-P(60)
// Allowed values: true false
TEST_F(RuleEngine_CONTEXT_KI_OSV_25_50, Opsparingsprodukt_SOME_SELECTED_POSITIVE) {
	TA ta { "15124040", 4}; // KonceptOid 4 - OSV
	ta.setValue(kMarkedspension_MK, true )
			.setValue(kTraditionel_MK, true)
			.setValue(kTidspensionMedGaranti_MK, false)
			.setValue(kLink_MK, false);

	auto r = re.validate(ta, {kMarkedspension_MK, kTraditionel_MK, kTidspensionMedGaranti_MK, kTidspensionUdenGaranti_MK, kLink_MK} );
	EXPECT_TRUE(r.isAllOk());
	cout << r;
}

// Test Opsparingsprodukter - PE(72, 73, 74, 75, 201)-P(60)
// Allowed values: true false
TEST_F(RuleEngine_CONTEXT_KI_OSV_25_50, Opsparingsprodukt_NEGATIVE) {
	TA ta { "15124040", 4}; // KonceptOid 4 - OSV
	ta.setValue(kMarkedspension_MK, true )
			.setValue(kTraditionel_MK, false)
			.setValue(kTidspensionMedGaranti_MK, false)
			.setValue(kLink_MK, false);
	ta.setValue(kStandardProduct, "Traditionel_MK");

	auto r = re.validate(ta, std::vector<unsigned short> {kStandardProduct} );
	EXPECT_FALSE(r.isAllOk());
	cout << r;
}
