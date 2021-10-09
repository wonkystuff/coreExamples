#include "dr1_defs.h"

const uint8_t sine[WTSIZE] PROGMEM = {
  0x80, 0x80, 0x81, 0x82, 0x83, 0x83, 0x84, 0x85, 0x86, 0x87, 0x87, 0x88, 0x89, 0x8a, 0x8a, 0x8b, 
  0x8c, 0x8d, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x91, 0x92, 0x93, 0x94, 0x94, 0x95, 0x96, 0x97, 0x98, 
  0x98, 0x99, 0x9a, 0x9b, 0x9b, 0x9c, 0x9d, 0x9e, 0x9e, 0x9f, 0xa0, 0xa1, 0xa1, 0xa2, 0xa3, 0xa4, 
  0xa4, 0xa5, 0xa6, 0xa7, 0xa7, 0xa8, 0xa9, 0xaa, 0xaa, 0xab, 0xac, 0xac, 0xad, 0xae, 0xaf, 0xaf, 
  0xb0, 0xb1, 0xb2, 0xb2, 0xb3, 0xb4, 0xb4, 0xb5, 0xb6, 0xb7, 0xb7, 0xb8, 0xb9, 0xb9, 0xba, 0xbb, 
  0xbb, 0xbc, 0xbd, 0xbd, 0xbe, 0xbf, 0xbf, 0xc0, 0xc1, 0xc1, 0xc2, 0xc3, 0xc3, 0xc4, 0xc5, 0xc5, 
  0xc6, 0xc7, 0xc7, 0xc8, 0xc9, 0xc9, 0xca, 0xcb, 0xcb, 0xcc, 0xcc, 0xcd, 0xce, 0xce, 0xcf, 0xcf, 
  0xd0, 0xd1, 0xd1, 0xd2, 0xd2, 0xd3, 0xd4, 0xd4, 0xd5, 0xd5, 0xd6, 0xd7, 0xd7, 0xd8, 0xd8, 0xd9, 
  0xd9, 0xda, 0xda, 0xdb, 0xdb, 0xdc, 0xdd, 0xdd, 0xde, 0xde, 0xdf, 0xdf, 0xe0, 0xe0, 0xe1, 0xe1, 
  0xe2, 0xe2, 0xe3, 0xe3, 0xe4, 0xe4, 0xe5, 0xe5, 0xe6, 0xe6, 0xe6, 0xe7, 0xe7, 0xe8, 0xe8, 0xe9, 
  0xe9, 0xea, 0xea, 0xea, 0xeb, 0xeb, 0xec, 0xec, 0xec, 0xed, 0xed, 0xee, 0xee, 0xee, 0xef, 0xef, 
  0xf0, 0xf0, 0xf0, 0xf1, 0xf1, 0xf1, 0xf2, 0xf2, 0xf2, 0xf3, 0xf3, 0xf3, 0xf4, 0xf4, 0xf4, 0xf5, 
  0xf5, 0xf5, 0xf5, 0xf6, 0xf6, 0xf6, 0xf7, 0xf7, 0xf7, 0xf7, 0xf8, 0xf8, 0xf8, 0xf8, 0xf9, 0xf9, 
  0xf9, 0xf9, 0xf9, 0xfa, 0xfa, 0xfa, 0xfa, 0xfb, 0xfb, 0xfb, 0xfb, 0xfb, 0xfb, 0xfc, 0xfc, 0xfc, 
  0xfc, 0xfc, 0xfc, 0xfc, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfe, 0xfe, 0xfe, 0xfe, 
  0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 
  0xff, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 
  0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfc, 0xfc, 0xfc, 
  0xfc, 0xfc, 0xfc, 0xfc, 0xfb, 0xfb, 0xfb, 0xfb, 0xfb, 0xfb, 0xfa, 0xfa, 0xfa, 0xfa, 0xf9, 0xf9, 
  0xf9, 0xf9, 0xf9, 0xf8, 0xf8, 0xf8, 0xf8, 0xf7, 0xf7, 0xf7, 0xf7, 0xf6, 0xf6, 0xf6, 0xf5, 0xf5, 
  0xf5, 0xf5, 0xf4, 0xf4, 0xf4, 0xf3, 0xf3, 0xf3, 0xf2, 0xf2, 0xf2, 0xf1, 0xf1, 0xf1, 0xf0, 0xf0, 
  0xf0, 0xef, 0xef, 0xee, 0xee, 0xee, 0xed, 0xed, 0xec, 0xec, 0xec, 0xeb, 0xeb, 0xea, 0xea, 0xea, 
  0xe9, 0xe9, 0xe8, 0xe8, 0xe7, 0xe7, 0xe6, 0xe6, 0xe6, 0xe5, 0xe5, 0xe4, 0xe4, 0xe3, 0xe3, 0xe2, 
  0xe2, 0xe1, 0xe1, 0xe0, 0xe0, 0xdf, 0xdf, 0xde, 0xde, 0xdd, 0xdd, 0xdc, 0xdb, 0xdb, 0xda, 0xda, 
  0xd9, 0xd9, 0xd8, 0xd8, 0xd7, 0xd7, 0xd6, 0xd5, 0xd5, 0xd4, 0xd4, 0xd3, 0xd2, 0xd2, 0xd1, 0xd1, 
  0xd0, 0xcf, 0xcf, 0xce, 0xce, 0xcd, 0xcc, 0xcc, 0xcb, 0xcb, 0xca, 0xc9, 0xc9, 0xc8, 0xc7, 0xc7, 
  0xc6, 0xc5, 0xc5, 0xc4, 0xc3, 0xc3, 0xc2, 0xc1, 0xc1, 0xc0, 0xbf, 0xbf, 0xbe, 0xbd, 0xbd, 0xbc, 
  0xbb, 0xbb, 0xba, 0xb9, 0xb9, 0xb8, 0xb7, 0xb7, 0xb6, 0xb5, 0xb4, 0xb4, 0xb3, 0xb2, 0xb2, 0xb1, 
  0xb0, 0xaf, 0xaf, 0xae, 0xad, 0xac, 0xac, 0xab, 0xaa, 0xaa, 0xa9, 0xa8, 0xa7, 0xa7, 0xa6, 0xa5, 
  0xa4, 0xa4, 0xa3, 0xa2, 0xa1, 0xa1, 0xa0, 0x9f, 0x9e, 0x9e, 0x9d, 0x9c, 0x9b, 0x9b, 0x9a, 0x99, 
  0x98, 0x98, 0x97, 0x96, 0x95, 0x94, 0x94, 0x93, 0x92, 0x91, 0x91, 0x90, 0x8f, 0x8e, 0x8d, 0x8d, 
  0x8c, 0x8b, 0x8a, 0x8a, 0x89, 0x88, 0x87, 0x87, 0x86, 0x85, 0x84, 0x83, 0x83, 0x82, 0x81, 0x80, 
  };
const uint8_t ramp[WTSIZE] PROGMEM = {
  0x80, 0x80, 0x80, 0x80, 0x81, 0x81, 0x81, 0x81, 0x82, 0x82, 0x82, 0x82, 0x83, 0x83, 0x83, 0x83, 
  0x84, 0x84, 0x84, 0x84, 0x85, 0x85, 0x85, 0x85, 0x86, 0x86, 0x86, 0x86, 0x87, 0x87, 0x87, 0x87, 
  0x88, 0x88, 0x88, 0x88, 0x89, 0x89, 0x89, 0x89, 0x8a, 0x8a, 0x8a, 0x8a, 0x8b, 0x8b, 0x8b, 0x8b, 
  0x8c, 0x8c, 0x8c, 0x8c, 0x8d, 0x8d, 0x8d, 0x8d, 0x8e, 0x8e, 0x8e, 0x8e, 0x8f, 0x8f, 0x8f, 0x8f, 
  0x90, 0x90, 0x90, 0x90, 0x91, 0x91, 0x91, 0x91, 0x92, 0x92, 0x92, 0x92, 0x93, 0x93, 0x93, 0x93, 
  0x94, 0x94, 0x94, 0x94, 0x95, 0x95, 0x95, 0x95, 0x96, 0x96, 0x96, 0x96, 0x97, 0x97, 0x97, 0x97, 
  0x98, 0x98, 0x98, 0x98, 0x99, 0x99, 0x99, 0x99, 0x9a, 0x9a, 0x9a, 0x9a, 0x9b, 0x9b, 0x9b, 0x9b, 
  0x9c, 0x9c, 0x9c, 0x9c, 0x9d, 0x9d, 0x9d, 0x9d, 0x9e, 0x9e, 0x9e, 0x9e, 0x9f, 0x9f, 0x9f, 0x9f, 
  0xa0, 0xa0, 0xa0, 0xa0, 0xa1, 0xa1, 0xa1, 0xa1, 0xa2, 0xa2, 0xa2, 0xa2, 0xa3, 0xa3, 0xa3, 0xa3, 
  0xa4, 0xa4, 0xa4, 0xa4, 0xa5, 0xa5, 0xa5, 0xa5, 0xa6, 0xa6, 0xa6, 0xa6, 0xa7, 0xa7, 0xa7, 0xa7, 
  0xa8, 0xa8, 0xa8, 0xa8, 0xa9, 0xa9, 0xa9, 0xa9, 0xaa, 0xaa, 0xaa, 0xaa, 0xab, 0xab, 0xab, 0xab, 
  0xac, 0xac, 0xac, 0xac, 0xad, 0xad, 0xad, 0xad, 0xae, 0xae, 0xae, 0xae, 0xaf, 0xaf, 0xaf, 0xaf, 
  0xb0, 0xb0, 0xb0, 0xb0, 0xb1, 0xb1, 0xb1, 0xb1, 0xb2, 0xb2, 0xb2, 0xb2, 0xb3, 0xb3, 0xb3, 0xb3, 
  0xb4, 0xb4, 0xb4, 0xb4, 0xb5, 0xb5, 0xb5, 0xb5, 0xb6, 0xb6, 0xb6, 0xb6, 0xb7, 0xb7, 0xb7, 0xb7, 
  0xb8, 0xb8, 0xb8, 0xb8, 0xb9, 0xb9, 0xb9, 0xb9, 0xba, 0xba, 0xba, 0xba, 0xbb, 0xbb, 0xbb, 0xbb, 
  0xbc, 0xbc, 0xbc, 0xbc, 0xbd, 0xbd, 0xbd, 0xbd, 0xbe, 0xbe, 0xbe, 0xbe, 0xbf, 0xbf, 0xbf, 0xbf, 
  0xc0, 0xc0, 0xc0, 0xc0, 0xc1, 0xc1, 0xc1, 0xc1, 0xc2, 0xc2, 0xc2, 0xc2, 0xc3, 0xc3, 0xc3, 0xc3, 
  0xc4, 0xc4, 0xc4, 0xc4, 0xc5, 0xc5, 0xc5, 0xc5, 0xc6, 0xc6, 0xc6, 0xc6, 0xc7, 0xc7, 0xc7, 0xc7, 
  0xc8, 0xc8, 0xc8, 0xc8, 0xc9, 0xc9, 0xc9, 0xc9, 0xca, 0xca, 0xca, 0xca, 0xcb, 0xcb, 0xcb, 0xcb, 
  0xcc, 0xcc, 0xcc, 0xcc, 0xcd, 0xcd, 0xcd, 0xcd, 0xce, 0xce, 0xce, 0xce, 0xcf, 0xcf, 0xcf, 0xcf, 
  0xd0, 0xd0, 0xd0, 0xd0, 0xd1, 0xd1, 0xd1, 0xd1, 0xd2, 0xd2, 0xd2, 0xd2, 0xd3, 0xd3, 0xd3, 0xd3, 
  0xd4, 0xd4, 0xd4, 0xd4, 0xd5, 0xd5, 0xd5, 0xd5, 0xd6, 0xd6, 0xd6, 0xd6, 0xd7, 0xd7, 0xd7, 0xd7, 
  0xd8, 0xd8, 0xd8, 0xd8, 0xd9, 0xd9, 0xd9, 0xd9, 0xda, 0xda, 0xda, 0xda, 0xdb, 0xdb, 0xdb, 0xdb, 
  0xdc, 0xdc, 0xdc, 0xdc, 0xdd, 0xdd, 0xdd, 0xdd, 0xde, 0xde, 0xde, 0xde, 0xdf, 0xdf, 0xdf, 0xdf, 
  0xe0, 0xe0, 0xe0, 0xe0, 0xe1, 0xe1, 0xe1, 0xe1, 0xe2, 0xe2, 0xe2, 0xe2, 0xe3, 0xe3, 0xe3, 0xe3, 
  0xe4, 0xe4, 0xe4, 0xe4, 0xe5, 0xe5, 0xe5, 0xe5, 0xe6, 0xe6, 0xe6, 0xe6, 0xe7, 0xe7, 0xe7, 0xe7, 
  0xe8, 0xe8, 0xe8, 0xe8, 0xe9, 0xe9, 0xe9, 0xe9, 0xea, 0xea, 0xea, 0xea, 0xeb, 0xeb, 0xeb, 0xeb, 
  0xec, 0xec, 0xec, 0xec, 0xed, 0xed, 0xed, 0xed, 0xee, 0xee, 0xee, 0xee, 0xef, 0xef, 0xef, 0xef, 
  0xf0, 0xf0, 0xf0, 0xf0, 0xf1, 0xf1, 0xf1, 0xf1, 0xf2, 0xf2, 0xf2, 0xf2, 0xf3, 0xf3, 0xf3, 0xf3, 
  0xf4, 0xf4, 0xf4, 0xf4, 0xf5, 0xf5, 0xf5, 0xf5, 0xf6, 0xf6, 0xf6, 0xf6, 0xf7, 0xf7, 0xf7, 0xf7, 
  0xf8, 0xf8, 0xf8, 0xf8, 0xf9, 0xf9, 0xf9, 0xf9, 0xfa, 0xfa, 0xfa, 0xfa, 0xfb, 0xfb, 0xfb, 0xfb, 
  0xfc, 0xfc, 0xfc, 0xfc, 0xfd, 0xfd, 0xfd, 0xfd, 0xfe, 0xfe, 0xfe, 0xfe, 0xff, 0xff, 0xff, 0xff, 
  };
const uint8_t sq[WTSIZE] PROGMEM = {
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  };
const uint8_t triangle[WTSIZE] PROGMEM = {
  0x80, 0x80, 0x81, 0x81, 0x82, 0x82, 0x83, 0x83, 0x84, 0x84, 0x85, 0x85, 0x86, 0x86, 0x87, 0x87, 
  0x88, 0x88, 0x89, 0x89, 0x8a, 0x8a, 0x8b, 0x8b, 0x8c, 0x8c, 0x8d, 0x8d, 0x8e, 0x8e, 0x8f, 0x8f, 
  0x90, 0x90, 0x91, 0x91, 0x92, 0x92, 0x93, 0x93, 0x94, 0x94, 0x95, 0x95, 0x96, 0x96, 0x97, 0x97, 
  0x98, 0x98, 0x99, 0x99, 0x9a, 0x9a, 0x9b, 0x9b, 0x9c, 0x9c, 0x9d, 0x9d, 0x9e, 0x9e, 0x9f, 0x9f, 
  0xa0, 0xa0, 0xa1, 0xa1, 0xa2, 0xa2, 0xa3, 0xa3, 0xa4, 0xa4, 0xa5, 0xa5, 0xa6, 0xa6, 0xa7, 0xa7, 
  0xa8, 0xa8, 0xa9, 0xa9, 0xaa, 0xaa, 0xab, 0xab, 0xac, 0xac, 0xad, 0xad, 0xae, 0xae, 0xaf, 0xaf, 
  0xb0, 0xb0, 0xb1, 0xb1, 0xb2, 0xb2, 0xb3, 0xb3, 0xb4, 0xb4, 0xb5, 0xb5, 0xb6, 0xb6, 0xb7, 0xb7, 
  0xb8, 0xb8, 0xb9, 0xb9, 0xba, 0xba, 0xbb, 0xbb, 0xbc, 0xbc, 0xbd, 0xbd, 0xbe, 0xbe, 0xbf, 0xbf, 
  0xc0, 0xc0, 0xc1, 0xc1, 0xc2, 0xc2, 0xc3, 0xc3, 0xc4, 0xc4, 0xc5, 0xc5, 0xc6, 0xc6, 0xc7, 0xc7, 
  0xc8, 0xc8, 0xc9, 0xc9, 0xca, 0xca, 0xcb, 0xcb, 0xcc, 0xcc, 0xcd, 0xcd, 0xce, 0xce, 0xcf, 0xcf, 
  0xd0, 0xd0, 0xd1, 0xd1, 0xd2, 0xd2, 0xd3, 0xd3, 0xd4, 0xd4, 0xd5, 0xd5, 0xd6, 0xd6, 0xd7, 0xd7, 
  0xd8, 0xd8, 0xd9, 0xd9, 0xda, 0xda, 0xdb, 0xdb, 0xdc, 0xdc, 0xdd, 0xdd, 0xde, 0xde, 0xdf, 0xdf, 
  0xe0, 0xe0, 0xe1, 0xe1, 0xe2, 0xe2, 0xe3, 0xe3, 0xe4, 0xe4, 0xe5, 0xe5, 0xe6, 0xe6, 0xe7, 0xe7, 
  0xe8, 0xe8, 0xe9, 0xe9, 0xea, 0xea, 0xeb, 0xeb, 0xec, 0xec, 0xed, 0xed, 0xee, 0xee, 0xef, 0xef, 
  0xf0, 0xf0, 0xf1, 0xf1, 0xf2, 0xf2, 0xf3, 0xf3, 0xf4, 0xf4, 0xf5, 0xf5, 0xf6, 0xf6, 0xf7, 0xf7, 
  0xf8, 0xf8, 0xf9, 0xf9, 0xfa, 0xfa, 0xfb, 0xfb, 0xfc, 0xfc, 0xfd, 0xfd, 0xfe, 0xfe, 0xff, 0xff, 
  0xff, 0xff, 0xfe, 0xfe, 0xfd, 0xfd, 0xfc, 0xfc, 0xfb, 0xfb, 0xfa, 0xfa, 0xf9, 0xf9, 0xf8, 0xf8, 
  0xf7, 0xf7, 0xf6, 0xf6, 0xf5, 0xf5, 0xf4, 0xf4, 0xf3, 0xf3, 0xf2, 0xf2, 0xf1, 0xf1, 0xf0, 0xf0, 
  0xef, 0xef, 0xee, 0xee, 0xed, 0xed, 0xec, 0xec, 0xeb, 0xeb, 0xea, 0xea, 0xe9, 0xe9, 0xe8, 0xe8, 
  0xe7, 0xe7, 0xe6, 0xe6, 0xe5, 0xe5, 0xe4, 0xe4, 0xe3, 0xe3, 0xe2, 0xe2, 0xe1, 0xe1, 0xe0, 0xe0, 
  0xdf, 0xdf, 0xde, 0xde, 0xdd, 0xdd, 0xdc, 0xdc, 0xdb, 0xdb, 0xda, 0xda, 0xd9, 0xd9, 0xd8, 0xd8, 
  0xd7, 0xd7, 0xd6, 0xd6, 0xd5, 0xd5, 0xd4, 0xd4, 0xd3, 0xd3, 0xd2, 0xd2, 0xd1, 0xd1, 0xd0, 0xd0, 
  0xcf, 0xcf, 0xce, 0xce, 0xcd, 0xcd, 0xcc, 0xcc, 0xcb, 0xcb, 0xca, 0xca, 0xc9, 0xc9, 0xc8, 0xc8, 
  0xc7, 0xc7, 0xc6, 0xc6, 0xc5, 0xc5, 0xc4, 0xc4, 0xc3, 0xc3, 0xc2, 0xc2, 0xc1, 0xc1, 0xc0, 0xc0, 
  0xbf, 0xbf, 0xbe, 0xbe, 0xbd, 0xbd, 0xbc, 0xbc, 0xbb, 0xbb, 0xba, 0xba, 0xb9, 0xb9, 0xb8, 0xb8, 
  0xb7, 0xb7, 0xb6, 0xb6, 0xb5, 0xb5, 0xb4, 0xb4, 0xb3, 0xb3, 0xb2, 0xb2, 0xb1, 0xb1, 0xb0, 0xb0, 
  0xaf, 0xaf, 0xae, 0xae, 0xad, 0xad, 0xac, 0xac, 0xab, 0xab, 0xaa, 0xaa, 0xa9, 0xa9, 0xa8, 0xa8, 
  0xa7, 0xa7, 0xa6, 0xa6, 0xa5, 0xa5, 0xa4, 0xa4, 0xa3, 0xa3, 0xa2, 0xa2, 0xa1, 0xa1, 0xa0, 0xa0, 
  0x9f, 0x9f, 0x9e, 0x9e, 0x9d, 0x9d, 0x9c, 0x9c, 0x9b, 0x9b, 0x9a, 0x9a, 0x99, 0x99, 0x98, 0x98, 
  0x97, 0x97, 0x96, 0x96, 0x95, 0x95, 0x94, 0x94, 0x93, 0x93, 0x92, 0x92, 0x91, 0x91, 0x90, 0x90, 
  0x8f, 0x8f, 0x8e, 0x8e, 0x8d, 0x8d, 0x8c, 0x8c, 0x8b, 0x8b, 0x8a, 0x8a, 0x89, 0x89, 0x88, 0x88, 
  0x87, 0x87, 0x86, 0x86, 0x85, 0x85, 0x84, 0x84, 0x83, 0x83, 0x82, 0x82, 0x81, 0x81, 0x80, 0x80, 
  };
