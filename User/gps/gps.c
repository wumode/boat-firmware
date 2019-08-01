#include "gps.h"


void AnalysisGPS(char* line) {
        switch (minmea_sentence_id(line, false)) {
            case MINMEA_SENTENCE_RMC: {
				struct minmea_sentence_rmc minmea_sentence_rmc_frame;
                if (minmea_parse_rmc(&minmea_sentence_rmc_frame, line)) {
					if(minmea_sentence_rmc_frame.valid){
						gps_data.latitude = minmea_tocoord(&minmea_sentence_rmc_frame.latitude);
						gps_data.longitude = minmea_tocoord(&minmea_sentence_rmc_frame.longitude);
						gps_data.speed = minmea_tocoord(&minmea_sentence_rmc_frame.speed);
						gps_updated = 1;
						//gps_initialized = 1;
					}
                }
                else {
                }
            } break;

            case MINMEA_SENTENCE_GGA: {
                struct minmea_sentence_gga minmea_sentence_gga_frame;
                if (minmea_parse_gga(&minmea_sentence_gga_frame, line)) {
					if(minmea_sentence_gga_frame.fix_quality){
						gps_data.latitude = minmea_tocoord(&minmea_sentence_gga_frame.latitude);
						gps_data.longitude = minmea_tocoord(&minmea_sentence_gga_frame.longitude);
						//gps_initialized = 1;
						gps_updated = 1;
					}
                }
                else {
                }
            } break;
			case MINMEA_SENTENCE_VTG: {

            } break;
            case MINMEA_INVALID: {
                
            } break;

            default: {
                
            } break;
        }
}
