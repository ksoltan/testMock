/** File: Particle.h
 *  Purpose: Redefine some Particle-defined types for use in unit-testing (compilation on PC)
**/

#include <string>
typedef std::string String; // Particle defines its own String class

enum PublishFlags {
  PUBLIC,
  PRIVATE,
  WITH_ACK
};

class Particle {
  // Example usage from arisense-fw-v18: Particle.Publish("DATA_V18", BUF_STRINGS.back(), PRIVATE, WITH_ACK)
  virtual boolean Publish(String eventName, String data, PublishFlags, PublishFlags);
};
