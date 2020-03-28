#define APPROVALS_DOCTEST
#include <ApprovalTests.hpp>

#define ImageApprovals_CONFIG_IMPLEMENT
#define ImageApprovals_CONFIG_WITH_LIBPNG
#include <ImageApprovals.hpp>

using namespace ImageApprovals;
using namespace ApprovalTests;

auto dirDisposer = Approvals::useApprovalsSubdirectory("../approval_tests");

auto comparatorDisposer
    = ImageComparator::registerForAllExtensions<ThresholdCompareStrategy>();
