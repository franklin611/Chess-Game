class Observer {
 public:
  virtual void notify(Vec start, Vec end) = 0;
  virtual ~Observer();
};
