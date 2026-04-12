#pragma once

#include <Arduino.h>

#include <math.h>
#include "NmeaChecksum.h"

// Send NMEA sentence WITHOUT the "*hh" part (we append checksum + CRLF).
static inline void nmea_send(const char* s_no_checksum) {
  const int cs = nmea0183_checksum(s_no_checksum);
  Serial.printf("%s*%02X\r\n", s_no_checksum, cs);
}

static inline float wrap360f_(float deg) {
  while (deg < 0.0f) deg += 360.0f;
  while (deg >= 360.0f) deg -= 360.0f;
  return deg;
}

// $--HDM,xxx.x,M*hh  (magnetic heading)
static inline void nmea_hdm(const char* talker2, float heading_deg) {
  char s[82];
  heading_deg = wrap360f_(heading_deg);
  snprintf(s, sizeof(s), "$%sHDM,%.1f,M", talker2, (double)heading_deg);
  nmea_send(s);
}

// $--ROT,x.x,A*hh  (rate of turn, degrees per minute; A=valid, V=invalid)
static inline void nmea_rot(const char* talker2, float rot_deg_per_min, bool valid) {
  char s[82];
  // pypilot typically sends ROT in deg/min; sign may need flip depending on your axis convention
  snprintf(s, sizeof(s), "$%sROT,%.1f,%c", talker2, (double)rot_deg_per_min, valid ? 'A' : 'V');
  nmea_send(s);
}

// $--XDR,A,x.x,D,PTCH*hh  (angular displacement in degrees)
// $--XDR,A,x.x,D,ROLL*hh
static inline void nmea_xdr_pitch_roll(const char* talker2, float pitch_deg, float roll_deg) {
  char s[82];
  // Keep it short to stay under 82 chars
  snprintf(s, sizeof(s), "$%sXDR,A,%.1f,D,PTCH", talker2, (double)pitch_deg);
  nmea_send(s);
  snprintf(s, sizeof(s), "$%sXDR,A,%.1f,D,ROLL", talker2, (double)roll_deg);
  nmea_send(s);
}

// $--XDR,D,x.x,M,HEAVE_1*hh  (heave / vertical displacement, meters)
static inline void nmea_xdr_heave(const char* talker2, float heave_m) {
  char s[82];
  snprintf(s, sizeof(s), "$%sXDR,D,%.4f,M,HEAVE_1", talker2, (double)heave_m);
  nmea_send(s);
}

// $--XDR,D,x.x,M,ENVEL_H_1*hh  (heave envelope, meters)
static inline void nmea_xdr_heave_envel(const char* talker2, float heave_m) {
  char s[82];
  snprintf(s, sizeof(s), "$%sXDR,D,%.4f,M,ENVEL_H_1", talker2, (double)heave_m);
  nmea_send(s);
}

// $--XDR,F,x.x,H,FREQ_A_1*hh  (dominant wave accel frequency, Hz)
static inline void nmea_xdr_freq_accel(const char* talker2, float freq_hz) {
  char s[82];
  snprintf(s, sizeof(s), "$%sXDR,F,%.4f,H,FREQ_A_1", talker2, (double)freq_hz);
  nmea_send(s);
}

// $--XDR,A,x.x,D,WAVE_ANG_1*hh
static inline void nmea_xdr_wave_angle(const char* talker2, float wave_angle_deg) {
  char s[82];
  // Keep it short to stay under 82 chars
  snprintf(s, sizeof(s), "$%sXDR,A,%.1f,D,WAVE_ANG_1", talker2, (double)wave_angle_deg);
  nmea_send(s);
}


// $--XDR,G,x.x,,WAVE_DSIGN_1*hh
static inline void nmea_xdr_wave_dir_sign(const char* talker2, int wave_dir_sign) {
  char s[82];
  // Keep it short to stay under 82 chars
  snprintf(s, sizeof(s), "$%sXDR,G,%d,,WAVE_DSIGN_1", talker2, wave_dir_sign);
  nmea_send(s);
}
