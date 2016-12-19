/*
 * Copyright 2016 Intel Corporation All Rights Reserved.
 *
 * The source code contained or described herein and all documents related to the
 * source code ("Material") are owned by Intel Corporation or its suppliers or
 * licensors. Title to the Material remains with Intel Corporation or its suppliers
 * and licensors. The Material contains trade secrets and proprietary and
 * confidential information of Intel or its suppliers and licensors. The Material
 * is protected by worldwide copyright and trade secret laws and treaty provisions.
 * No part of the Material may be used, copied, reproduced, modified, published,
 * uploaded, posted, transmitted, distributed, or disclosed in any way without
 * Intel's prior express written permission.
 *
 * No license under any patent, copyright, trade secret or other intellectual
 * property right is granted to or conferred upon you by disclosure or delivery of
 * the Materials, either expressly, by implication, inducement, estoppel or
 * otherwise. Any license under such intellectual property rights must be express
 * and approved by Intel in writing.
 */

#ifndef InternalSctp_h
#define InternalSctp_h

#include "MediaFramePipeline.h"
#include "RawTransport.h"
#include "SctpTransport.h"

namespace woogeen_base {

class InternalSctp : public FrameSource, public FrameDestination, public RawTransportListener {
public:
    InternalSctp();
    virtual ~InternalSctp();

    unsigned int getLocalUdpPort() { return m_transport->getLocalUdpPort(); }
    unsigned int getLocalSctpPort() { return m_transport->getLocalSctpPort(); }

    void connect(const std::string &ip, unsigned int udpPort, unsigned int sctpPort);

    // Implements FrameSource
    void onFeedback(const FeedbackMsg&);

    // Implements FrameDestination
    void onFrame(const Frame&);

    // Implements RawTransportListener.
    void onTransportData(char* buf, int len);
    void onTransportError() { }
    void onTransportConnected() { }

private:
    boost::shared_ptr<woogeen_base::SctpTransport> m_transport;
};

} /* namespace woogeen_base */

#endif /* InternalSctp_h */