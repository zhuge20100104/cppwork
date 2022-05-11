#ifndef _FREDRIC_TRACER_HPP_
#define _FREDRIC_TRACER_HPP_
#include "glog/logging.h"

class sort_tracer {
    private:
        int value;
        int generation;
        static long n_created;
        static long n_destroyed;
        static long n_assigned;
        static long n_compared;
        static long n_max_live;

        static void update_max_live() {
            if(n_created - n_destroyed > n_max_live) {
                n_max_live = n_created - n_destroyed;
            }
        }

    public:
        static long creations() {
            return n_created;
        }

        static long destructions() {
            return n_destroyed;
        }

        static long assignments() {
            return n_assigned;
        }

        static long comparisons() {
            return n_compared;
        }

        static long max_live() {
            return n_max_live;
        }

    public:
        sort_tracer(int v = 0): value(v), generation(1) {
            ++n_created;
            update_max_live();
            LOG(INFO) << "sort_tracer #" << n_created
                << ", created generation " << generation
                << " (total: " << n_created - n_destroyed
                << ")\n";
        }

        ~sort_tracer() {
            ++n_destroyed;
            update_max_live();
            LOG(INFO) << "sort_tracer generation " << generation
                << " destroyed (total: "
                << n_created - n_destroyed << ")\n";
        }

        sort_tracer& operator=(sort_tracer const& b) {
            ++n_assigned;
            LOG(INFO) << "sort_tracer assignment #" << n_assigned
                << "(generation " << generation
                << " = " << b.generation
                << ")\n";
            value = b.value;
            return *this;
        }

        friend bool operator< (sort_tracer const& a, sort_tracer const& b) {
            ++n_compared;
            LOG(INFO) << "sort_tracer comparison #" << n_compared
                << "(generation " << a.generation
                << " < " << b.generation
                << ")\n";
            return a.value < b.value;
        }

        int val() const {
            return value;
        }

};
#endif