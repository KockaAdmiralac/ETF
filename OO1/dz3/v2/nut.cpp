#include "nut.hpp"

NutritivnaVrednost operator+(const NutritivnaVrednost &nv1, const NutritivnaVrednost &nv2) {
    return {
        nv1.uh + nv2.uh,
        nv1.masti + nv2.masti,
        nv1.proteini + nv2.proteini
    };
}

std::ostream &operator<<(std::ostream &it, const NutritivnaVrednost &nv) {
    nv.pisi(it);
    return it;
}

void NutritivnaVrednost::pisi(std::ostream &it) const {
    it << "[uh: " << uh << ", ma: " << masti << ", pr: " << proteini
       << "]";
}
