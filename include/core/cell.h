#pragma once

namespace cas {
    struct Cell {
        /* Parameterized constructor: Initializes cell with the given state */
        Cell(bool state) : state(state) {}

        /* State of the cell: true = alive, false = dead */
        bool state;
    };
}