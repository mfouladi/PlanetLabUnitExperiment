#ifndef UNITEXPERIMENT_H
#define UNITEXPERIMENT_H

int unitExperimentSender(int num_of_packets, int inter_packet_departure_spacing,
                     int probe_packet_length, int entropy, 
                     char* experiment_run_log_absolute_filename);
int unitExperimentReceiver();
#endif
