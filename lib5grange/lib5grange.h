/* ***************************************/
/* Copyright Notice                      */
/* Copyright(c)2020 5G Range Consortium  */
/* All rights Reserved                   */
/*****************************************/

#ifndef INCLUDED_LIB5GRANGE_H
#define INCLUDED_LIB5GRANGE_H

#include <cstdint>
#include <complex>
#include <complex.h>
#include <vector>
#include <array>
#include <memory>

#define ALL_TERMINAL (0xF)
#define BS_TERMINAL  (0x0)

#define LAST_RB (131)
#define MAX_NUM_RB (132)
#define SAMPLE_RATE (30.72e6f)
#define RB_BANDWIDTH (180.0e3f)
#define POLAR_MAX_CW_LEN (2048)
#define POLAR_CRC_LEN (16)

/** DCI Size in QAM symbols **/
#define NUM_RB_PER_DCI (11)

namespace lib5grange {
    using namespace std;

    //These values are based on table from INATEL
    //Define SNR to MCS mapping. If SNR is greater than or equals to i and is lesser than j, then MCS = j.
    constexpr float mappingSNRtoMCS[] = {-6.1, -3.6, -2.4, -1.3, -0.4, 1, 2.2, 6.6, 7.3, 7.9, 9, 
    10.1, 11, 12, 13.5, 14.5, 15.9, 17.2, 18.6, 19.2, 20.7, 21.5, 25.6, 26.6, 27.2, 27.8, 28.7};

 typedef struct {
        unsigned k;                       /**< Number of subcarriers */
        unsigned m;                       /**< Number of subsimbols */
        unsigned ncp;                     /**< Number of samples in the CP */
        unsigned ncs;                     /**< Number of samples in the CS */
        unsigned nw;                      /**< number of windowng samples */
        unsigned kon;                     /**< Number of active subcarriers */
        unsigned koff;                    /**< Number of inactive subcarriers */
        float a;                          /**< roll-off factor */
        unsigned subcarriers_per_rb;      /**< Number of subcarrires per RB */
        unsigned symbols_per_subframe;    /**< Number of samples in a subframe */
        unsigned pilot_dt;                /**< Pilot spacing in time  */
        unsigned pilot_df;                /**< Pilot spacing in frequency */
        unsigned num_pilot_sc;            /**< Number of pilot subcarriers */
        unsigned num_dci_sc;              /**< Number of subcarriers used for control dci*/
        unsigned num_dci_qam;             /**< Number of control QAM symbols */
    } numerology_cfg_t;
 
 constexpr numerology_cfg_t numerology[] = 
    {    
            {/** Numerology 0 definition **/
                .k   = 16384,
                .m   = 4,
                .ncp = 4352,
                .ncs = 768,
                .nw  = 512,
                .kon = 12672,
                .koff = 3712,
                .a   = 0,
                .subcarriers_per_rb = 96,
                .symbols_per_subframe = 2,
                .pilot_dt = 2,
                .pilot_df = 4,
                .num_pilot_sc = 3168,
                .num_dci_sc   = 32,  // dci: first 32 subcarriers of allocation
                .num_dci_qam  = 224, // dci: net number of RE on dci
            },

            {/** Numerology 1 definition **/
                .k   = 8192,
                .m   = 4,
                .ncp = 2176,
                .ncs = 384,
                .nw  = 256,
                .kon = 6336,
                .koff = 1856,
                .a   = 0,
                .subcarriers_per_rb = 48,
                .symbols_per_subframe = 4,
                .pilot_dt = 4,
                .pilot_df = 4,
                .num_pilot_sc = 1584,
                .num_dci_sc   = 16,  // dci: first 16 subcarriers of allocation
                .num_dci_qam  = 240, // dci: net number of RE on dci
            },

            {/** Numerology 2 definition **/
                .k   = 	4096,
                .m   = 	4,
                .ncp = 	1088,
                .ncs =	192,
                .nw  =	128,
                .kon = 	3168,
                .koff = 928,
                .a   = 	0,
                .subcarriers_per_rb  = 24,
                .symbols_per_subframe = 8,
                .pilot_dt =	4,
                .pilot_df =	4,
                .num_pilot_sc = 792,
                .num_dci_sc   = 8,   // dci: first 8 subcarriers of allocation
                .num_dci_qam  = 240, // dci: net number of RE on dci

            },

            {/** Numerology 3 definition **/
                .k   = 	2048,
                .m   = 	4,
                .ncp = 	544,
                .ncs =	96,
                .nw  =	64,
                .kon = 	1584,
                .koff = 464,
                .a   = 	0,
                .subcarriers_per_rb   = 12,
                .symbols_per_subframe = 16,
                .pilot_dt =	4,
                .pilot_df =	4,
                .num_pilot_sc = 396,
                .num_dci_sc   = 4,   // dci: first 4 subcarriers of allocation
                .num_dci_qam  = 240, // dci: net number of RE on dci
            },

            {/** Numerology 4 definition **/
                .k   = 	1024,
                .m   = 	4,
                .ncp = 	272,
                .ncs =	48,
                .nw  =	32,
                .kon = 	792,
                .koff = 232,
                .a   = 	0,
                .subcarriers_per_rb   = 6,
                .symbols_per_subframe = 32,
                .pilot_dt =	4,
                .pilot_df =	3,
                .num_pilot_sc = 264,
                .num_dci_sc   = 2 ,  // dci: first 2 subcarriers of allocation
                .num_dci_qam  = 224, // dci: net number of RE on dci

            },

            {/** Numerology 5 definition **/
                .k   = 	1024,
                .m   = 	2,
                .ncp = 	136,
                .ncs =	24,
                .nw  =	16,
                .kon = 	792,
                .koff = 232,
                .a   = 	0,
                .subcarriers_per_rb   = 6,
                .symbols_per_subframe = 64,
                .pilot_dt =	4,
                .pilot_df =	6,
                .num_pilot_sc = 132,
                .num_dci_sc   = 2 ,  // dci: first 2 subcarriers of allocation
                .num_dci_qam  = 224, // dci: net number of RE on dci
            }
    };

    
    /** QAM mdodulation enum type. 
     *  The value is the number of bits per symbol in each modulation
     */
    typedef enum {
        QPSK   = 2,     /**<   QPSK - 2 bits per symbol**/
        QAM16  = 4,     /**<  16QAM - 4 bits per symbol**/
        QAM64  = 6,     /**<  64QAM - 6 bits per symbol**/
        QAM256 = 8      /**< 256QAM - 8 bits per symbol**/
    } qammod_t;
    
    constexpr qammod_t mcsToModulation[] =
        {
            QPSK,   //MCS 0 (filler)
            QPSK,   //MCS 1
            QPSK,   //MCS 2
            QPSK,   //MCS 3
            QPSK,   //MCS 4
            QPSK,   //MCS 5
            QPSK,   //MCS 6
            QPSK,   //MCS 7
            QAM16,  //MCS 8
            QAM16,  //MCS 9
            QAM16,  //MCS 10
            QAM16,  //MCS 11
            QAM16,  //MCS 12
            QAM16,  //MCS 13
            QAM16,  //MCS 14
            QAM16,  //MCS 15
            QAM16,  //MCS 16
            QAM64,  //MCS 17
            QAM64,  //MCS 18
            QAM64,  //MCS 19
            QAM64,  //MCS 20
            QAM64,  //MCS 21
            QAM64,  //MCS 22
            QAM256, //MCS 23
            QAM256, //MCS 24
            QAM256, //MCS 25
            QAM256, //MCS 26
            QAM256  //MCS 27
        };

    constexpr float mcsToCodeRate[] =
        {
            0.04167,   //MCS 0 (filler)
            0.04167,   //MCS 1
            0.08333,   //MCS 2
            0.12500,   //MCS 3
            0.06250,   //MCS 4
            0.20833,   //MCS 5
            0.29167,   //MCS 6
            0.37500,   //MCS 7
            0.20833,   //MCS 8
            0.25000,   //MCS 9
            0.29167,   //MCS 10
            0.37500,   //MCS 11
            0.45833,   //MCS 12
            0.54167,   //MCS 13
            0.62500,   //MCS 14
            0.75000,   //MCS 15
            0.83333,   //MCS 16
            0.58333,   //MCS 17
            0.66667,   //MCS 18
            0.75000,   //MCS 19
            0.79167,   //MCS 20
            0.87500,   //MCS 21
            0.91667,   //MCS 22
            0.75000,   //MCS 23
            0.83333,   //MCS 24
            0.87500,   //MCS 25
            0.91667,   //MCS 26
            0.95833    //MCS 27
        };

    /**
     * @brief Transform any basic C type into bytes 
     * 
     * Method used to transform any C basic type to a sequance of bytes and
     * and push at the end of thevector given as argument
     * 
     * @tparam T: type
     * @param num: number to be serialized 
     * @param v: vector where the bytes will be stored 
     */
    template <typename T>
    void push_bytes(vector<uint8_t> & v, T num){
        for(int i=0; i<sizeof(num); i++) {
            v.push_back(*(((uint8_t*) &num )+i));
        }
    }


    template <typename T>
    void pop_bytes(T & num, vector<uint8_t> & v){
        T* ptr = (T*) (&v.back()-sizeof(T)+1); 
        num = *ptr;
        v.erase(v.end()-sizeof(T), v.end());
    }


    /**
     * @brief Transform a vector of any basic C type into bytes 
     * 
     * @tparam T: type 
     * @param newdata: Vector to be serialized 
     * @param bytes: vector where the bytes data will be appended 
     */
    template <typename T>
    void serialize_vector(vector<uint8_t> & bytes, vector<T> & newdata){
        size_t num_bytes_of_newdata = sizeof(T)*newdata.size();
        size_t newsize = bytes.size() + num_bytes_of_newdata;
        size_t last = bytes.size();
        bytes.resize(newsize);
        uint8_t * newdata_byte_ptr = (uint8_t*) newdata.data(); 
        for (size_t i=0; i<num_bytes_of_newdata; i++){
            bytes[last+i] = newdata_byte_ptr[i];
        }
        push_bytes(bytes, newdata.size()); // push the vector length
    }

    /**
     * @brief Recover a vector from bytes
     * 
     * @tparam T : type
     * @param v : Vector to be serialized 
     * @param bytes : vector where the bytes data will be appended 
     */
    template <typename T>
    inline void deserialize_vector(vector<T> & v, vector<uint8_t> & bytes){
        size_t num_elements;           
        pop_bytes(num_elements, bytes); // Retrieve the vector size
        v.resize(num_elements);         // space for the data
        T* first_element_ptr = ((T*) (&bytes.back() + 1)) - num_elements; // Find the first
        for(int i=0; i<num_elements; i++){
            v[i]=first_element_ptr[i];
        }
        bytes.resize(bytes.size()-num_elements*sizeof(T));
    }


    /** Definition of MIMO configuration type **/
    typedef enum {
        NONE = 0,           /**< SISO **/          
        DIVERSITY = 1,      /**< Space Time block coding **/
        MULTIPLEXING = 2    /**< Spatial multiplexing **/
    } mimo_scheme_t;
    
    /** MIMO configuration struct **/
    typedef struct{
        mimo_scheme_t scheme  = NONE; /**< MIMO Scheme **/
        size_t num_tx_antenas = 1;    /**< Number of transmitting antennas **/
        size_t precoding_mtx  = 0;    /**< MIMO Precoding matrix selection **/
        
        /** Serializatyion method for the struct**/
        void serialize(vector<uint8_t> & bytes)
        {
            push_bytes(bytes, scheme);
            push_bytes(bytes, num_tx_antenas);
            push_bytes(bytes, precoding_mtx);
        }

        /** deserializatyion method for the struct (inverse order)**/
        void deserialize(vector<uint8_t> & bytes){
            pop_bytes(precoding_mtx, bytes);
            pop_bytes(num_tx_antenas, bytes);
            pop_bytes(scheme, bytes);
        }
    }mimo_cfg_t;
    
    
     /** Resource allocation configuration struct **/
    typedef struct{
        uint8_t target_ue_id = ALL_TERMINAL; /**< 16 bit ID of the target terminal **/
        uint8_t first_rb = 0;                  /**< First alocated resource block  **/
        uint8_t number_of_rb = 132;            /**< Number of allocatced resource blocks  **/
        
        /** Serializatyion method for the struct**/
        void serialize(vector<uint8_t> & bytes)
        {
            push_bytes(bytes, target_ue_id);
            push_bytes(bytes, first_rb);
            push_bytes(bytes, number_of_rb);
        }
        /** deserializatyion method for the struct (inverse order)**/
        void deserialize(vector<uint8_t> & bytes){
            pop_bytes(number_of_rb, bytes);
            pop_bytes(first_rb, bytes);
            pop_bytes(target_ue_id, bytes);
        }


    }allocation_cfg_t;

    /** Modulation and coding configuration struct **/
    typedef struct{
        qammod_t modulation;           /**< Modulation  **/
        size_t power_offset = 0;       /**< Power offset in dB for the transmission **/
        size_t num_info_bytes = 0;     /**< Number of information bits  **/
        size_t num_coded_bytes = 0;    /**< Number of coded bits  **/
        
        /** Serializatyion method for the struct**/
        void serialize(vector<uint8_t> & bytes)
        {
            push_bytes(bytes, modulation);
            push_bytes(bytes, power_offset);
            push_bytes(bytes, num_info_bytes);
            push_bytes(bytes, num_coded_bytes);
        }
        /** deserializatyion method for the struct (inverse order)**/
        void deserialize(vector<uint8_t> & bytes){
            pop_bytes(num_coded_bytes, bytes);
            pop_bytes(num_info_bytes, bytes);
            pop_bytes(power_offset, bytes);
            pop_bytes(modulation, bytes);
        }
        
    } mcs_cfg_t;
    
    
    /** MAC/PHY info struct **/
    typedef struct {
        uint8_t sequence_number = 0;       /**< Sequence number of the transport block  **/
        unsigned  subframe_number = 0;     /**< Subframe number  **/
        bool  last_tb_in_subframe = false; /**< Indicates if this is the last transport block in the subframe  **/
        bool first_tb_in_subframe = false; /**< Indicates if this is the last transport block in the subframe  **/
    
        /** 
         * \brief Serializatyion method for the struct
         * This method convert all menbers of the struct to a sequance of bytes and appends at the end
         * of the vector given as argument
         * 
         *  @param bytes: vector of bytes where the struct will be serialized
         **/
        void serialize(vector<uint8_t> & bytes)
        {
            push_bytes(bytes, sequence_number);
            push_bytes(bytes, subframe_number);
            push_bytes(bytes, last_tb_in_subframe);
            push_bytes(bytes, first_tb_in_subframe);
        }
        /** deserializatyion method for the struct (inverse order)**/
        void deserialize(vector<uint8_t> & bytes){
            pop_bytes(first_tb_in_subframe, bytes);
            pop_bytes(last_tb_in_subframe, bytes);
            pop_bytes(subframe_number, bytes);
            pop_bytes(sequence_number, bytes);

        }        
    } macphyctl_t;
    
    /** 
    * Calculates the  amout of bytes available for transmission using the given configuration
    * @param numID: (0 - 5) Number identifying the 5G Range numerology according to D3.2.
    * @param allocation: Struct with the configuration of the resource allocation (see: allocation_cfg_t).
    * @param mimo: Struct with the configuration of the MIMO (see: mimo_cfg_t).
    **/
    inline size_t get_re_capacity(
        const size_t & numID,                 // Numerology ID
        const allocation_cfg_t & allocation,  // Allocation config struct
        const mimo_cfg_t & mimo);             // MIMO config struct
    
   /**
    * @brief Calculates the gross amount of bits available for transmission using the given configuration
    * 
    * This function calculates the amount of bits available for transmission using the given configuration
    * PHY configuration and resource allocation.
    * 
    *  @param numID : (0 - 5) Number identifying the 5G Range numerology according to D3.2.
    *  @param allocation: Struct with the configuration of the resource allocation (see: allocation_cfg_t).
    *  @param mimo: Struct with the configuration of the MIMO (see: mimo_cfg_t).
    *  @param mod: QAM modulation (QPSK, QAM16, QAM64 or QAM256).
    *  @return size_t 
    */
    inline size_t get_bit_capacity(
        const size_t & numID,
        const allocation_cfg_t & allocation,    
        const mimo_cfg_t & mimo,
        const qammod_t & mod);

    /** 
     * @brief Calculates the gross amount of bits available for transmission using the given configuration
     *  @param numRE: Number of Resorce elements.
     *  @param mod: QAM modulation (QPSK, QAM16, QAM64 or QAM256).
    **/
    size_t get_bit_capacity(
        const size_t & numRE, // Number of resource elements
        const qammod_t & mod); // Modulation
    
    /**
    * Returns the number of resource blocks required to transmit a given number of bits
    * with a given modulation and a taget code-rate.
    *   
    *   @param numID: (0 - 5) Number identifying the 5G Range numerology according to D3.2.
    *   @param mimo: Struct with the configuration of the MIMO (see: mimo_cfg_t).
    *   @param mod: QAM modulation (QPSK, QAM16, QAM64 or QAM256).
    *   @param target_coderate: The target coderate for the tranmission.
    *   @param info_bits: Number of information bits to be sent.
    **/
    inline size_t get_num_required_rb(
        const size_t & numID,    // Numerology ID
        const mimo_cfg_t & mimo, // MIMO Onfiguration
        const qammod_t & mod,    // Modulation 
        float target_coderate,   // Target coderate
        size_t info_bits);       // number of infromation bits
    
    /**
     * @brief This class represents a transport block sent by the MAC and holds all configuration required by the PHY
     * for the transmission.
     * 
     */
    class MacPDU {
        private:

        public:
            unsigned numID_;                    /**< Numerology ID **/
            macphyctl_t macphy_ctl_;            /**< MAC to PHY control struct **/          
            allocation_cfg_t allocation_;       /**< allocation: Struct with the configuration of the resource allocation (see: allocation_cfg_t). **/
            mimo_cfg_t mimo_;                   /**< Struct with the configuration of the MIMO (see: mimo_cfg_t). **/
            mcs_cfg_t  mcs_;                    /**< /** Struct with the regarding Modulation and coding configuration (see: mcs_cfg_t) **/
            uint8_t rankIndicator_;              /**<  Rank indicator **/ 
            float snr_avg_;                      /**< Average SNR measured **/            
            // Data section
            std::vector<uint8_t> mac_data_ {};            /**< Uncoded information bits from MAC. **/
            std::vector<uint8_t> coded_data_ {};          /**< Coded bits to be transmitted. **/
            std::vector<std::complex<float>> symbols_ {}; /**< QAM symbols to be transmitted  **/
            std::array<std::vector<std::complex<float>>,2> mimo_symbols_ {}; /**< MIMO encoded information symbols**/

            // DCI / UCI
            std::vector<uint8_t> control_data_ {};                 /**< Coded control information bits to be transmitted **/
            std::array<std::vector<std::complex<float>>,2> control_symbols_ {};  /**< Control QAM symbols to be transmitted **/

            /** @brief Construct a empty new MacPDU object */
            MacPDU();
            
            /** 
             * @brief Construct a MAC PDU object with the specified configuration parameters.
             * @param numID : Numerology id
             * @param phyctl: MAC/PHY control struct
             * @param allocation: allocation config struct
             * @param mimo_cfg: mimo config struct
             * @param mcs_cfg: modulation and coding config struct
            **/
            MacPDU(unsigned numID, macphyctl_t phyctl, allocation_cfg_t allocation, mimo_cfg_t mimo_cfg, mcs_cfg_t mcs_cfg);
            
            /**
             * @brief Construct a new MacPDU object from a serialized byte sequence (see: MacPDU::serialize()).
             * @param bytes: vector of bytes with the srialized object 
             */
            MacPDU(vector<uint8_t> & bytes);
                      
            /** @brief Destroy the MacPDU object **/
            inline  ~MacPDU(){};
            
            /** Serializes the MacPDU object to a sequance of bytes **/
            void serialize(vector<uint8_t> & bytes);
           
    }; /* class MacPDU */

    size_t
    inline get_re_capacity(
        const size_t & numID,                   // Numerology ID
        const allocation_cfg_t & allocation,    // Allocation config struct
        const mimo_cfg_t & mimo = {NONE, 1, 0}) // MIMO config struct (defaults to SISO)
    {
        size_t numRB = allocation.number_of_rb;
        if (numRB==0){return 0;}
        const auto & subcarriers = numerology[numID].subcarriers_per_rb;
        const auto & subsymbols  = numerology[numID].m;
        const auto & symbols     = numerology[numID].symbols_per_subframe;
        const auto & df          = numerology[numID].pilot_df;
        const auto & dt          = numerology[numID].pilot_dt;
        const auto & dci_size    = numerology[numID].num_dci_qam;
        size_t numRE = subcarriers * subsymbols * symbols;
        numRE = numRE - numRE/(df*dt);                                              // Account for REs used for pilots
        numRE = (numRE * numRB) - dci_size - dci_size*((numRB-1)/NUM_RB_PER_DCI);   // Account for REs used for DCI
        if (mimo.scheme==MULTIPLEXING){
            numRE = numRE * mimo.num_tx_antenas;
        }
        return numRE;
    }

    /**
     * @brief Get the RE capacity from PDU object
     * 
     * @param pdu 
     * @return size_t 
     */
    size_t
    inline get_re_capacity(const MacPDU & pdu) 
    {
        const auto & numID = pdu.numID_;
        const auto & allocation = pdu.allocation_;
        const auto & mimo = pdu.mimo_;
        return get_re_capacity(numID, allocation, mimo);
    }

    size_t
    inline get_bit_capacity(
        const size_t & numID,
        const allocation_cfg_t & allocation,    
        const mimo_cfg_t & mimo,
        const qammod_t & mod)
    {
        size_t numRE = get_re_capacity(numID, allocation, mimo);
        size_t numBits = (numRE*mod);
        return numBits;
    }

    size_t
    inline get_bit_capacity(const MacPDU & pdu)
    {   
        const auto & numID = pdu.numID_;
        const auto & allocation = pdu.allocation_;
        const auto & mimo = pdu.mimo_;
        const auto & mod = pdu.mcs_.modulation;

        return get_bit_capacity(numID, allocation, mimo, mod);
    }

    size_t
    inline get_bit_capacity(
        const size_t & numRE, // Number of resource elements
        const qammod_t & mod) // Modulation
    {
        return (numRE*mod);
    }

    size_t 
    inline get_num_required_rb(
        const size_t & numID,    // Numerology ID
        const mimo_cfg_t & mimo, // MIMO Onfiguration
        const qammod_t & mod,    // Modulation 
        float target_coderate,   // Target coderate
        size_t info_bits)        // number of information bits
    {
        float required_bit_capacity = round((float)info_bits/target_coderate);
        allocation_cfg_t aloc = {
            .target_ue_id =0,
            .first_rb=0,
            .number_of_rb=1
            };
        auto & dci_size = numerology[numID].num_dci_qam;
        size_t gross_rb_bit_capacity = get_bit_capacity(numID,aloc,mimo,mod) + (dci_size*mod);
        size_t gross_qam_capacity = gross_rb_bit_capacity/mod;
        size_t num_qam_required = (size_t) round(required_bit_capacity / mod); //round odr ceil
        num_qam_required += dci_size;   // Account for the first DCI
        num_qam_required += (((num_qam_required-dci_size)/gross_qam_capacity))/NUM_RB_PER_DCI * dci_size; // Account for extra DCIs
        size_t numRB = (size_t) ceil(float(num_qam_required)/float(gross_qam_capacity));
        return numRB;
    } /* get_mum_required_rb */ 

    inline MacPDU::MacPDU(){
        numID_ = 0;
        snr_avg_ = 10;
		rankIndicator_ = 10;
        mac_data_   = {};
        coded_data_ = {};
        symbols_ = {};
        mimo_symbols_[0] = {};
        mimo_symbols_[1] = {};
        control_symbols_[0] = {};
        control_symbols_[1] = {};
    }

    inline MacPDU::MacPDU(
        unsigned numID,                 // Numerology ID
        macphyctl_t phyctl,             // phyctl MAC/PHY control struct
        allocation_cfg_t allocation,    // allocation config
        mimo_cfg_t mimo_cfg,            // MIMO config
        mcs_cfg_t mcs_cfg)              // modulation and coding config
    {
        numID_ = numID;
        macphy_ctl_ = phyctl;
        allocation_ = allocation;
        mimo_ = mimo_cfg;
        mcs_ = mcs_cfg;
        snr_avg_ = 10;
		rankIndicator_ = 10;
        
    } /*MacPDU()*/

    inline void
    MacPDU::serialize(vector<uint8_t> & bytes)
    {
        push_bytes(bytes, numID_);
        macphy_ctl_.serialize(bytes);
        allocation_.serialize(bytes);
        mimo_.serialize(bytes);
        mcs_.serialize(bytes);
        push_bytes(bytes, snr_avg_);
		push_bytes(bytes, rankIndicator_);
        // Vectors
        serialize_vector(bytes, mac_data_);
        // serialize_vector(bytes, coded_data_);
        // serialize_vector(bytes, symbols_);
        // serialize_vector(bytes, control_data_);
        // serialize_vector(bytes, control_symbols_[0]);
        // serialize_vector(bytes, control_symbols_[1]);
        // serialize_vector(bytes, mimo_symbols_[0]);
        // serialize_vector(bytes, mimo_symbols_[1]);
    }

    inline MacPDU::MacPDU(vector<uint8_t> & bytes)
    {
        // deserialize_vector(mimo_symbols_[1], bytes);
        // deserialize_vector(mimo_symbols_[0], bytes);
        // deserialize_vector(control_symbols_[1], bytes);
        // deserialize_vector(control_symbols_[0], bytes);
        // deserialize_vector(control_data_, bytes);
        // deserialize_vector(symbols_, bytes);
        // deserialize_vector(coded_data_, bytes);
        deserialize_vector(mac_data_, bytes);
        // non-vectors
        pop_bytes(rankIndicator_, bytes);
		pop_bytes(snr_avg_, bytes);
        mcs_.deserialize(bytes);
        mimo_.deserialize(bytes);
        allocation_.deserialize(bytes);
        macphy_ctl_.deserialize(bytes);
        pop_bytes(numID_, bytes);
    }

    inline size_t
    get_net_byte_capacity(float coderate, const MacPDU & pdu)
    {
        return ((get_bit_capacity(pdu)/8) * coderate);
    };

    inline size_t
    get_net_byte_capacity(
        size_t numID,
        allocation_cfg_t allocation,
        mimo_cfg_t mimo,
        qammod_t mod,
        float coderate)
    {
        return (get_bit_capacity(numID, allocation, mimo, mod)/8 * coderate);
    }


} /* namespace lib5grange */
#endif /* INCLUDED_LIB5GRANGE_H */
