#define APPROVALS_DOCTEST
#include <ApprovalTests.hpp>
#include <ImageApprovals.hpp>

using namespace ImageApprovals;
using namespace ApprovalTests;

auto dirDisposer = Approvals::useApprovalsSubdirectory("../approval_tests");

auto comparatorDisposer
    = FileApprover::registerComparatorForExtension(
        ".png", Comparator::make<ThresholdImageComparator>(
            AbsThreshold(1.5 / 255.0), Percent(0.01)));
