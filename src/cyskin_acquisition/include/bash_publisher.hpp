
#include "skin_publisher.hpp"

class BashPublisher : public SkinPublisher
{
private:
    /* data */
public:
    BashPublisher( std::shared_ptr<UpdaterInterface> _u , double _print_freq, double _thresh );
    ~BashPublisher();
    void publish();
};

