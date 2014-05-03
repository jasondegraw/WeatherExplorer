#ifndef LOGGING_H
#define LOGGING_H

#include <boost/log/trivial.hpp>
#include <boost/log/sinks/basic_sink_backend.hpp>

#include <string>
#include <boost/shared_ptr.hpp>
#include <boost/phoenix.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/sync_frontend.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/utility/formatting_ostream.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/support/date_time.hpp>

#define LOG(lvl)\
    BOOST_LOG_STREAM_WITH_PARAMS(::boost::log::trivial::logger::get(),\
        (::boost::log::keywords::severity = ::boost::log::trivial::lvl))

namespace logging {

// Class to handle logging output
template <class T> class SinkBackend
        : public boost::log::sinks::basic_formatted_sink_backend<char, boost::log::sinks::synchronized_feeding>
{
public:
    SinkBackend(T output);
    void consume(boost::log::record_view const& rec, string_type const& formatted);
private:
    T m_output;
};

template <class T> SinkBackend<T>::SinkBackend(T output) : boost::log::sinks::basic_formatted_sink_backend<char, boost::log::sinks::synchronized_feeding>()
{
    m_output = output;
}

template <class T> void SinkBackend<T>::consume(boost::log::record_view const& rec, string_type const& formatted)
{
    m_output->store(formatted);
}

// Function to initialize the logging setup
template <class T> void initialize(T output)
{
    boost::shared_ptr<boost::log::core> core = boost::log::core::get();

    boost::shared_ptr< boost::log::sinks::synchronous_sink<SinkBackend<T> > > sink(new boost::log::sinks::synchronous_sink<SinkBackend<T> >(output));

    // Set the formatter
    sink->set_formatter(boost::log::expressions::stream
                        // line id will be written in hex, 8-digits, zero-filled
                        //<< std::hex << std::setw(8) << std::setfill('0') << expr::attr< unsigned int >("LineID")
                        //<< ": "
                        << boost::log::expressions::format_date_time< boost::posix_time::ptime >("TimeStamp", "%Y-%m-%d %H:%M:%S")
                        <<" <" << boost::log::trivial::severity
                        << "> " << boost::log::expressions::smessage);

    core->add_sink(sink);

    // Add attributes that we will use
    boost::log::add_common_attributes();
}

}


#endif // LOGGING_H
