#include "ai.h"
#include "statistics.h"

#include "df/historical_entity.h"
#include "df/ui.h"
#include "df/world.h"

REQUIRE_GLOBAL(ui);
REQUIRE_GLOBAL(world);
REQUIRE_GLOBAL(cur_year);
REQUIRE_GLOBAL(cur_year_tick);

Statistics::Statistics(AI *ai) :
		ai(ai), onupdate_handle(nullptr), onstatechange_handle(nullptr), file_writer(
				"./statistics-wealth.csv",
				std::ofstream::out | std::ofstream::app) {
	// TODO: I think there's a dfhack::filesystem api we can use to mkdir and check if files exist?

	// TODO: look at ui.h if you want to name this file after the fort. it has int32_t civ_id, site_id, group_id, race_id, etc
}
Statistics::~Statistics() {
	events.onupdate_unregister(onupdate_handle);
	events.onstatechange_unregister(onstatechange_handle);
}

command_result Statistics::startup(color_ostream & out) {
	file_writer << "Time,Wealth" << endl;
	return CR_OK;
}
command_result Statistics::onupdate_register(color_ostream & out) {
	onupdate_handle = events.onupdate_register("df-ai statistics", 1000, 100,
			[this](color_ostream & out) {update(out);});
	onstatechange_handle = events.onstatechange_register(
			[](color_ostream & out, state_change_event mode)
			{
				// TODO: do something when the state changes.
			});
	return CR_OK;
}
command_result Statistics::onupdate_unregister(color_ostream & out) {
	events.onupdate_unregister(onupdate_handle);
	events.onstatechange_unregister(onstatechange_handle);
	return CR_OK;
}

void Statistics::update(color_ostream & out) {
	//	out << "fortress firstname: " << ui->main.fortress_entity->name.first_name
	//			<< endl; // blank?
	//	out << "fortress nickname: " << ui->main.fortress_entity->name.nickname
	//			<< endl; // blank?
	//	out << "fortress nickname: ";
	//	for(int i=0; i < 7; i++) out << ui->main.fortress_entity->name.words[i];
	//	out<< endl; // all -1?

	//	out << "fortress" << world->world_data->name.

	// flip the status screen on to trigger an update to ui->tasks.wealth
	AI::feed_key(interface_key::D_STATUS);
	AI::feed_key(interface_key::LEAVESCREEN);

	file_writer << world->frame_counter << "," << ui->tasks.wealth.total
			<< endl;

}
void Statistics::ignore_pause() {

}
std::string Statistics::status() {
	return "running normally... i guess...";
}

