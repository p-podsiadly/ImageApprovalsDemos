#define APPROVALS_DOCTEST
#include <ApprovalTests.hpp>
#include <ImageApprovals.hpp>

using namespace ImageApprovals;
using namespace ApprovalTests;

auto dirDisposer = Approvals::useApprovalsSubdirectory("../approval_tests");

auto comparatorDisposer
    = Comparator::registerForAllExtensions<ThresholdCompareStrategy>();
