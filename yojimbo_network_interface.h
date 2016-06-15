/*
    Yojimbo Client/Server Network Library.

    Copyright © 2016, The Network Protocol Company, Inc.
    
    All rights reserved.

    Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

        1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

        2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer 
           in the documentation and/or other materials provided with the distribution.

        3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived 
           from this software without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, 
    INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
    DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
    SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR 
    SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
    WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
    USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef YOJIMBO_NETWORK_INTERFACE_H
#define YOJIMBO_NETWORK_INTERFACE_H

#include "yojimbo_config.h"

namespace yojimbo
{
    enum NetworkInterfaceFlags
    {
        NETWORK_INTERFACE_FLAG_INSECURE_MODE = (1<<0)
    };

    enum NetworkInterfaceCounters
    {
        NETWORK_INTERFACE_COUNTER_PACKETS_SENT,
        NETWORK_INTERFACE_COUNTER_PACKETS_RECEIVED,
        NETWORK_INTERFACE_COUNTER_PACKETS_READ,
        NETWORK_INTERFACE_COUNTER_PACKETS_WRITTEN,
        NETWORK_INTERFACE_COUNTER_SEND_QUEUE_OVERFLOW,
        NETWORK_INTERFACE_COUNTER_RECEIVE_QUEUE_OVERFLOW,
        NETWORK_INTERFACE_COUNTER_READ_PACKET_FAILURES,
        NETWORK_INTERFACE_COUNTER_WRITE_PACKET_FAILURES,
        NETWORK_INTERFACE_COUNTER_ENCRYPT_PACKET_FAILURES,
        NETWORK_INTERFACE_COUNTER_DECRYPT_PACKET_FAILURES,
        NETWORK_INTERFACE_COUNTER_ENCRYPTED_PACKETS_READ,
        NETWORK_INTERFACE_COUNTER_ENCRYPTED_PACKETS_WRITTEN,
        NETWORK_INTERFACE_COUNTER_UNENCRYPTED_PACKETS_READ,
        NETWORK_INTERFACE_COUNTER_UNENCRYPTED_PACKETS_WRITTEN,
        NETWORK_INTERFACE_COUNTER_ENCRYPTION_MAPPING_FAILURES,
        NETWORK_INTERFACE_COUNTER_NUM_COUNTERS
    };

    class NetworkInterface
    {
    public:

        virtual ~NetworkInterface() {}

        virtual Packet * CreatePacket( int type ) = 0;

        virtual void DestroyPacket( Packet * packet ) = 0;

        virtual void SendPacket( const Address & address, Packet * packet, uint64_t sequence = 0, bool immediate = false ) = 0;

        virtual Packet * ReceivePacket( Address & from, uint64_t * sequence = NULL ) = 0;

        virtual void WritePackets() = 0;

        virtual void ReadPackets() = 0;

        virtual int GetMaxPacketSize() const = 0;

        virtual void SetContext( void * context ) = 0;

        virtual void EnablePacketEncryption() = 0;

        virtual void DisableEncryptionForPacketType( int type ) = 0;

        virtual bool IsEncryptedPacketType( int type ) const = 0;

        virtual bool AddEncryptionMapping( const Address & address, const uint8_t * sendKey, const uint8_t * receiveKey ) = 0;

        virtual bool RemoveEncryptionMapping( const Address & address ) = 0;

        virtual void ResetEncryptionMappings() = 0;

        virtual void AdvanceTime( double time ) = 0;

        virtual double GetTime() const = 0;

        virtual uint64_t GetCounter( int index ) const = 0;

        virtual void SetFlags( uint64_t flags ) = 0;

        virtual uint64_t GetFlags() const = 0;

        virtual const Address & GetAddress() const = 0;
    };
}

#endif // #ifndef YOJIMBO_H
