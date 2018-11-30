#pragma once

void resetPacket(struct packet *pp);

void parseToPacket (int byte, uint32_t data, struct packet *pp);
