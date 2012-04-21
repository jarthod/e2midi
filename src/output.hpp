#ifndef OUTPUT_HPP
#define OUTPUT_HPP

class Output {
public:
  // trigger given input parameter (0 <= p <= 1)
  virtual void    trigger(float p) = 0;

};

#endif