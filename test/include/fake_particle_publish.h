#ifndef FAKE_PARTICLE_PUBLISH_H
#define FAKE_PARTICLE_PUBLISH_H

#include "fake_particle_string.h"
#include <vector>

enum PublishFlags {
  PUBLIC,
  PRIVATE,
  WITH_ACK
};

class FakeParticle {
public:
	void SetPublishReturnFlags(std::vector<bool> flags){publish_return_flags_ = flags;} // For testing
  // Example usage from arisense-fw-v18: Particle.Publish("DATA_V18",
  //                                                      BUF_STRINGS.back(),
  //                                                      PRIVATE, WITH_ACK)
  // Set -Wno-unused-parameter flag in Makefile to quiet warnings
  bool Publish(String eventName, String data,
                      PublishFlags=PublishFlags::PRIVATE,
                      PublishFlags=PublishFlags::WITH_ACK){
                        published_data_.push_back(data);
                        return publish_return_flags_.at(num_call++);
                      }

  String GetPublishedDataAt(int idx){
    return published_data_.at(idx);
  }

  // Call everytime you finish using FakeParticle in a test case.
  void Reset(){
    ResetPublishedData();
    ResetPublishReturnFlags();
  }

  void ResetPublishedData(){
    published_data_.clear();
  }

  void ResetPublishReturnFlags(){
    num_call = 0;
    publish_return_flags_.clear();
  }

private:
  int num_call;
  std::vector<bool> publish_return_flags_;
  std::vector<String> published_data_;
};

extern FakeParticle Particle; // Declared/initialized in test/main.cpp

#endif // FAKE_PARTICLE_PUBLISH_H
