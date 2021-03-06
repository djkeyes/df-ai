#pragma once

#include "event_manager.h"

#include <map>
#include <set>

#include "df/entity_position_responsibility.h"
#include "df/job_type.h"
#include "df/unit_labor.h"

namespace df
{
    struct building_civzonest;
    struct entity_position_assignment;
    struct squad;
    struct unit;
}

class AI;

class Population
{
    union pet_flags
    {
        uint32_t whole;
        struct
        {
            uint32_t milkable : 1;
            uint32_t shearable : 1;
            uint32_t hunts_vermin : 1;
            uint32_t grazer : 1;
        } bits;
    };

    AI *ai;
public:
    std::set<int32_t> citizen;
private:
    std::map<int32_t, int32_t> military;
    std::map<int32_t, pet_flags> pet;
    size_t update_counter;
    OnupdateCallback *onupdate_handle;
    std::set<int32_t> medic;
    std::vector<int32_t> workers;
    std::set<df::job_type> seen_badwork;

public:
    Population(AI *ai);
    ~Population();

    command_result startup(color_ostream & out);
    command_result onupdate_register(color_ostream & out);
    command_result onupdate_unregister(color_ostream & out);

    void update(color_ostream & out);

    void new_citizen(color_ostream & out, int32_t id);
    void del_citizen(color_ostream & out, int32_t id);

    void update_citizenlist(color_ostream & out);
    void update_jobs(color_ostream & out);
    void update_deads(color_ostream & out);
    void update_caged(color_ostream & out);
    void update_military(color_ostream & out);

    void military_random_squad_attack_unit(color_ostream & out, df::unit *u);
    void military_all_squads_attack_unit(color_ostream & out, df::unit *u);
    void military_squad_attack_unit(color_ostream & out, df::squad *squad, df::unit *u);
    std::string military_find_commander_pos();
    std::string military_find_captain_pos();

    df::unit *military_find_new_soldier(color_ostream & out, const std::vector<df::unit *> & unitlist);
    int32_t military_find_free_squad();

    void set_up_trading(bool should_be_trading);

    bool unit_hasmilitaryduty(df::unit *u);
    int32_t unit_totalxp(df::unit *u);

    static std::string positionCode(df::entity_position_responsibility responsibility);

    void update_nobles(color_ostream & out);
    void check_noble_appartments(color_ostream & out);

    df::entity_position_assignment *assign_new_noble(color_ostream & out, std::string pos_code, df::unit *unit);

    void update_pets(color_ostream & out);

    void assign_unit_to_zone(df::unit *u, df::building_civzonest *bld);

    std::string status();
};

// vim: et:sw=4:ts=4
