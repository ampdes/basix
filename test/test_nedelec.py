# Copyright (c) 2020 Chris Richardson
# FEniCS Project
# SPDX-License-Identifier: MIT

import fiatx
import pytest


@pytest.mark.parametrize("order", [1, 2, 3])
def test_nedelec2d(order):
    ned2 = fiatx.Nedelec(fiatx.CellType.triangle, order)
    print(ned2)


@pytest.mark.parametrize("order", [1, 2, 3])
def test_nedelec3d(order):
    ned3 = fiatx.Nedelec(fiatx.CellType.tetrahedron, order)
    print(ned3)