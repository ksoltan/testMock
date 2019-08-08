/** File: Particle.h
 *  Purpose: Redefine some Particle-defined types for use in unit-testing (compilation on PC)
**/
#ifndef PARTICLE_H
#define PARTICLE_H

#include <string>
#include <vector>

typedef std::string String; // Particle defines its own String class

enum PublishFlags {
  PUBLIC,
  PRIVATE,
  WITH_ACK
};

class FakeParticle {
public:
	void SetPublishFlag(bool flag){publish_flag_ = flag;} // For testing
  // Example usage from arisense-fw-v18: Particle.Publish("DATA_V18",
  //                                                      BUF_STRINGS.back(),
  //                                                      PRIVATE, WITH_ACK)
  // Will warn about unused variables.
  bool Publish(String eventName, String data,
                      PublishFlags=PublishFlags::PRIVATE,
                      PublishFlags=PublishFlags::WITH_ACK){
                        published_data_.push_back(data);
                        return publish_flag_;
                      }

  String GetPublishedDataAt(int idx){
    return published_data_.at(idx);
  }

  void ResetPublishedData(){
    published_data_.clear();
  }

private:
  bool publish_flag_;
  std::vector<String> published_data_;
};
extern FakeParticle Particle; // To use, declare in one test as FakeParticle Particle;

#endif // PARTICLE_H
