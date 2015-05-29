#include <string>
#include <vector>
#include <iostream>

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

class ContributionLadder_CONTEXT_KI_OSV_25_50 : public ::testing::Test  {
protected:
    virtual void SetUp() {
        re = RuleEngine();
        re.initConstants(get_file_contents("basedata-ruleconstants.json"));
        re.parseRuleCatalogueJSON(get_file_contents("rule-catalogue.json"));
        KonceptInfo ki {17, // UnderkonceptOid:OSV 25-49
        	{ { 1, "true"}, // Solidarisk faellestarif
			  { 6, "true"}, // SEB Firmapensionspulje
        	  {11, "true"}, // Parameter-Basis
			  {15, "true"} // FG-Spaend
        	} };
        re.initContext(ki);
    }

    RuleEngine re;
};


// Test kIndmeldelsesalder and getting options prior to that
TEST_F(ContributionLadder_CONTEXT_KI_OSV_25_50, Bidragsstigningsform_Ingen) {
	RuleEngine::_printDebugAtValidation = true;
	TA ta { "15124040", 4}; // KonceptOid 4 - OSV
	ta.setValue(kBidragsstigningsform, "Ingen" );

	// expecting complains about missing step
	auto r = re.validate(ta, false);
	EXPECT_FALSE(r.isAllOk());
//	if (r.isAllOk())
		cout << r;
	ASSERT_EQ(1, r.getValidationResults(kBidragstrappe).size());
	EXPECT_EQ(kProductElementRequired, r.getValidationResults(kBidragstrappe).at(0).getValidationCode());

	r = re.validate(ta, (unsigned short) kBidragsstigningsform );
	EXPECT_TRUE(r.isAllOk());
//	if (r.isAllOk())
		cout << r;

	r = re.validate(ta, {kBidragsstigningsform, kBidragstrappe} );
	EXPECT_TRUE(r.isAllOk());
//	if (r.isAllOk())
		cout << r;
	ASSERT_EQ(3, r.getWarnings(kBidragstrappe).size());
	EXPECT_EQ(kProductElementRequired, r.getWarnings(kBidragstrappe).at(0).getValidationCode());

	//  now add one step, but let it start from 3 (!=0), and it should fail
	ta.addContributionStep({3, 3.4, 5.3});
	r = re.validate(ta, false);
	EXPECT_FALSE(r.isAllOk());
//	if (r.isAllOk())
		cout << r;
	ASSERT_EQ(1, r.getValidationResults(kBidragstrappe).size());
	EXPECT_EQ(kValueNotAllowed, r.getValidationResults(kBidragstrappe).at(0).getValidationCode());

	//  now remove that step, and add one that starts from 0 and no complains
	ta.removeContributionStep({3, 0,0});
	ta.addContributionStep({0, 3.4, 5.3});
	r = re.validate(ta, false);
	EXPECT_TRUE(r.isAllOk());
//	if (!r.isAllOk())
		cout << r;


	//  then add one more and it should complain again, that only 1 step is allowed, when "Ingen" is selected in Bidragsstigningsform
	ta.addContributionStep({1, 5.4, 3.0});
	r = re.validate(ta, false);
	EXPECT_FALSE(r.isAllOk());
//	if (r.isAllOk())
		cout << r;
	ASSERT_EQ(1, r.getValidationResults(kBidragstrappe).size());
	EXPECT_EQ(kValueNotAllowed, r.getValidationResults(kBidragstrappe).at(0).getValidationCode());


	//  now remove the last step (index!=0), and everything should be fine again
	ta.removeContributionStep( {1, 0, 0} );
	r = re.validate(ta, false);
	EXPECT_TRUE(r.isAllOk());
//	if (!r.isAllOk())
		cout << r;
}

TEST_F(ContributionLadder_CONTEXT_KI_OSV_25_50, Bidragsstigningsform_Alder) {
	RuleEngine::_printDebugAtValidation = true;
	TA ta { "15124040", 4}; // KonceptOid 4 - OSV
	ta.setValue(kBidragsstigningsform, "Alder" );

	auto r = re.validate(ta, false);
	EXPECT_FALSE(r.isAllOk());
//	if (r.isAllOk())
		cout << r;
	ASSERT_EQ(1, r.getValidationResults(kBidragstrappe).size());
	EXPECT_EQ(kProductElementRequired, r.getValidationResults(kBidragstrappe).at(0).getValidationCode());

//	ta.addContributionStep( {} );
}
