/*
 *  NRF24L01+ library header file
 *
 *
 * Created: 5/11/2022 6:53:26 PM
 *  Author: Binari, Dasuni
 *
 * 	
 */
 
#include "../../defines.h"

#ifndef NRF24L01_H
#define NRF24L01_H


/* Public functions */


void nrf_init(nrf_opmode_t mode, uint8_t *address);
uint8_t nrf_transmit_packet(uint8_t *packet, uint8_t length);
uint8_t nrf_receive_packet(uint8_t *buf, uint8_t *length);
void nrf_set_ack_payload(uint8_t pipe, uint8_t *buf, uint8_t length);
void nrf_tx_data(uint8_t up_down, uint8_t left_right, uint8_t forward_backward, uint8_t siren, uint8_t auto_manual_mode);
int nrf_rx_data(uint8_t *up_down, uint8_t *left_right, uint8_t *forward_backward, uint8_t *siren, uint8_t *auto_manual_mode);


#endif  // NRF24L01_H
