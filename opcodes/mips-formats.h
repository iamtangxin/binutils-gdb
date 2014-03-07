/* mips-formats.h
   Copyright (C) 2013-2014 Free Software Foundation, Inc.

   This library is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3, or (at your option)
   any later version.

   It is distributed in the hope that it will be useful, but WITHOUT
   ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
   or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public
   License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; see the file COPYING3. If not,
   see <http://www.gnu.org/licenses/>.  */

/* For ARRAY_SIZE.  */
#include "libiberty.h"

#define INT_ADJ(SIZE, LSB, MAX_VAL, SHIFT, PRINT_HEX) \
  { \
    static const struct mips_int_operand op = { \
      { OP_INT, SIZE, LSB }, MAX_VAL, 0, SHIFT, PRINT_HEX \
    }; \
    return &op.root; \
  }

#define UINT(SIZE, LSB) \
  INT_ADJ(SIZE, LSB, (1 << (SIZE)) - 1, 0, FALSE)

#define SINT(SIZE, LSB) \
  INT_ADJ(SIZE, LSB, (1 << ((SIZE) - 1)) - 1, 0, FALSE)

#define HINT(SIZE, LSB) \
  INT_ADJ(SIZE, LSB, (1 << (SIZE)) - 1, 0, TRUE)

#define BIT(SIZE, LSB, BIAS) \
  { \
    static const struct mips_int_operand op = { \
      { OP_INT, SIZE, LSB }, (1 << (SIZE)) - 1, BIAS, 0, TRUE \
    }; \
    return &op.root; \
  }

#define MAPPED_INT(SIZE, LSB, MAP, PRINT_HEX) \
  { \
    typedef char ATTRIBUTE_UNUSED \
      static_assert[(1 << (SIZE)) == ARRAY_SIZE (MAP)]; \
    static const struct mips_mapped_int_operand op = { \
      { OP_MAPPED_INT, SIZE, LSB }, MAP, PRINT_HEX \
    }; \
    return &op.root; \
  }

#define MSB(SIZE, LSB, BIAS, ADD_LSB, OPSIZE) \
  { \
    static const struct mips_msb_operand op = { \
      { OP_MSB, SIZE, LSB }, BIAS, ADD_LSB, OPSIZE \
    }; \
    return &op.root; \
  }

#define REG(SIZE, LSB, BANK) \
  { \
    static const struct mips_reg_operand op = { \
      { OP_REG, SIZE, LSB }, OP_REG_##BANK, 0 \
    }; \
    return &op.root; \
  }

#define OPTIONAL_REG(SIZE, LSB, BANK) \
  { \
    static const struct mips_reg_operand op = { \
      { OP_OPTIONAL_REG, SIZE, LSB }, OP_REG_##BANK, 0 \
    }; \
    return &op.root; \
  }

#define MAPPED_REG(SIZE, LSB, BANK, MAP) \
  { \
    typedef char ATTRIBUTE_UNUSED \
      static_assert[(1 << (SIZE)) == ARRAY_SIZE (MAP)]; \
    static const struct mips_reg_operand op = { \
      { OP_REG, SIZE, LSB }, OP_REG_##BANK, MAP \
    }; \
    return &op.root; \
  }

#define OPTIONAL_MAPPED_REG(SIZE, LSB, BANK, MAP) \
  { \
    typedef char ATTRIBUTE_UNUSED \
      static_assert[(1 << (SIZE)) == ARRAY_SIZE (MAP)]; \
    static const struct mips_reg_operand op = { \
      { OP_OPTIONAL_REG, SIZE, LSB }, OP_REG_##BANK, MAP \
    }; \
    return &op.root; \
  }

#define REG_PAIR(SIZE, LSB, BANK, MAP) \
  { \
    typedef char ATTRIBUTE_UNUSED \
      static_assert1[(1 << (SIZE)) == ARRAY_SIZE (MAP##1)]; \
    typedef char ATTRIBUTE_UNUSED \
      static_assert2[(1 << (SIZE)) == ARRAY_SIZE (MAP##2)]; \
    static const struct mips_reg_pair_operand op = { \
      { OP_REG_PAIR, SIZE, LSB }, OP_REG_##BANK, MAP##1, MAP##2 \
    }; \
    return &op.root; \
  }

#define PCREL(SIZE, LSB, IS_SIGNED, SHIFT, ALIGN_LOG2, INCLUDE_ISA_BIT, \
              FLIP_ISA_BIT) \
  { \
    static const struct mips_pcrel_operand op = { \
      { { OP_PCREL, SIZE, LSB }, \
	(1 << ((SIZE) - (IS_SIGNED))) - 1, 0, SHIFT, TRUE }, \
      ALIGN_LOG2, INCLUDE_ISA_BIT, FLIP_ISA_BIT \
    }; \
    return &op.root.root; \
  }

#define JUMP(SIZE, LSB, SHIFT) \
  PCREL (SIZE, LSB, FALSE, SHIFT, SIZE + SHIFT, TRUE, FALSE)

#define JALX(SIZE, LSB, SHIFT) \
  PCREL (SIZE, LSB, FALSE, SHIFT, SIZE + SHIFT, TRUE, TRUE)

#define BRANCH(SIZE, LSB, SHIFT) \
  PCREL (SIZE, LSB, TRUE, SHIFT, 0, TRUE, FALSE)

#define SPECIAL(SIZE, LSB, TYPE) \
  { \
    static const struct mips_operand op = { OP_##TYPE, SIZE, LSB }; \
    return &op; \
  }
