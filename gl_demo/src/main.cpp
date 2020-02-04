#define APPROVALS_DOCTEST
#include <ApprovalTests.hpp>
#include <ImageApprovals.hpp>

using namespace ImageApprovals;
using namespace ApprovalTests;

auto dirDisposer = Approvals::useApprovalsSubdirectory("../approval_tests");

auto imgComparatorDisposer
    = Comparator::registerForAllExtensions<ThresholdImageComparator>(
        AbsThreshold(0.04), Percent(0.1));
