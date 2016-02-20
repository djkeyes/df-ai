/*
 * Utility for logging interesting game statistics, for review later
 */

#pragma once

#include "event_manager.h"

#include <iostream>

class AI;

class Statistics
{
    AI *ai;
    OnupdateCallback *onupdate_handle;
    OnstatechangeCallback *onstatechange_handle;
    std::ofstream file_writer;

public:
    Statistics(AI *ai);
    ~Statistics();

    command_result startup(color_ostream & out);
    command_result onupdate_register(color_ostream & out);
    command_result onupdate_unregister(color_ostream & out);

    void update(color_ostream & out);
    void ignore_pause();
    std::string status();
};

// vim: et:sw=4:ts=4
