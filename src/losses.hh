#pragma once

typedef struct kl_pair {
  unsigned k;
  unsigned l;
} kl_pair;

static const kl_pair attacker_losses[][4] =
{
  { {2, 2}, {0, 1}, {0, 0}, {0, 1} },
  { {1, 0}, {4, 4}, {1, 1}, {1, 0} },
  { {0, 1}, {2, 2}, {8, 8}, {2, 2} },
  { {1, 1}, {1, 0}, {1, 0}, {4, 4} }
};

static const kl_pair defender_losses[][4] =
{
  { {0, 0}, {1, 0}, {8, 0}, {1, 0} },
  { {0, 1}, {0, 0}, {1, 0}, {2, 1} },
  { {4, 1}, {2, 0}, {1, 0}, {0, 2} },
  { {1, 0}, {2, 1}, {0, 1}, {0, 0} }
};
