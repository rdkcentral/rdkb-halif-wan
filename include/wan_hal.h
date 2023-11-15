/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2023 RDK Management
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
*/
/**
 * 
 * @file wan_hal.h
 * @brief The wan_hal provides an interface to get/set WAN control features.
 */

#ifndef __WAN_HAL_H__
#define __WAN_HAL_H__

#include <stdint.h>

/**
 * @defgroup WAN_HAL WAN HAL
 *
 * @defgroup WAN_HAL_TYPES  WAN HAL Data Types
 * @ingroup  WAN_HAL
 *
 * @defgroup WAN_HAL_APIS   WAN HAL APIs
 * @ingroup  WAN_HAL
 *
 **/

/**
 * @addtogroup WAN_HAL_TYPES
 * @{
 */

#define RETURN_ERROR 1
#define RETURN_OK 0

#define BUFLEN_8 8
#define BUFLEN_32 32
#define BUFLEN_64 64

/**
* @enum t_eWanMode
* @brief Enumerates the possible WAN modes for the device.
*/
typedef enum
{
    WAN_MODE_DISABLED = 1, /**< WAN mode is disabled. */
    WAN_MODE_DSL_ONLY = 2, /**< WAN mode is DSL-only. */
    WAN_MODE_ETH_ONLY = 3, /**< WAN mode is Ethernet-only. */
    WAN_MODE_AUTO = 4      /**< Automatic WAN mode selection. */
} t_eWanMode;

/**
* @struct WAN_IPV4_CFG
* @brief Contains WAN IPv4 configuration
*/
typedef struct
_WAN_IPV4_CFG
{
    char ifname[64];         /**< Interface name (e.g., "erouter0"). */
    char subnetmask[64];     /**< Subnet mask (e.g., "255.255.255.0"). */
    char ipaddress[64];      /**< IP address to assign (e.g., "192.168.0.1"). */
    char dnsservers[256];    /**< New-line separated list of DNS servers to be added. */
    char defaultgateway[64]; /**< Default gateway address (e.g., "192.168.0.254"). */

} WAN_IPV4_CFG, *PWAN_IPV4_CFG;

/**
* @struct WAN_IPV6_CFG
* @brief Contains WAN IPv6 configuration
*/
typedef struct
_WAN_IPV6_CFG
{
    char ifname[64];         /**< Interface name (e.g., "erouter0"). */
    char ipaddress[128];     /**< IPv6 address to assign (e.g., "2001:db8::1"). */
    char dnsservers[512];    /**< New-line separated list of DNS servers to be added. */
    int preferredlifetime;   /**< Preferred lifetime for the IPv6 address. */
    int validlifetime;       /**< Valid lifetime for the IPv6 address. */

} WAN_IPV6_CFG, *PWAN_IPV6_CFG;

/**
* @struct WAN_QOS_QUEUE
* @brief The WAN_QOS_QUEUE structure needed in ccsp-wanagent and wan-hal
*/
typedef  struct
_WAN_QOS_QUEUE
{
    unsigned long       InstanceNumber;          /**< Instance number (1 to 128). */
    char                Alias[64];               /**< Alias or name for the queue. Possible values: Queue_1, Queue_2, ..., Queue_10. */
    unsigned long       queueKey;                /**< Queue key (0 to Maxqueues-1, vendor-specific). */
    unsigned char       queueEnable;             /**< Indicates if the queue is enabled (TRUE or FALSE). */
    char                queueStatus[256];        /**< Status of the queue (Disabled, Enabled). */
    char                queueInterface[256];     /**< Associated interface for the queue (e.g., erouter0). */
    unsigned long       queueWeight;             /**< Weight of the queue (0 to 100, vendor-specific). */
    unsigned long       queuePrecedence;         /**< Precedence of the queue (1 to 4294967295, vendor-specific). */
    unsigned long       REDThreshold;            /**< RED (Random Early Detection) threshold (1 to 100, vendor-specific). */
    char                dropAlgorithm[256];      /**< Drop algorithm used by the queue (e.g., DT, RED, WRED, vendor-specific). */
    char                schedulerAlgorithm[256]; /**< Scheduling algorithm used by the queue (e.g., SP, WRR, WFQ, vendor-specific). */
    signed long         shapingRate;             /**< Shaping rate for the queue (-1 to 2147483647, vendor-specific). */
    unsigned long       shapingBurstSize;        /**< Burst size for queue shaping (0 to max burst size, vendor-specific). */
    signed long         MinBitRate;              /**< Minimum bit rate for the queue (-1 to 2147483647, vendor-specific). */
    char                QueueName[256];          /**< Name of the queue (e.g., WAN Q1, WAN Q2, ..., WAN Q10). */
    signed long         DslLatency;              /**< DSL latency for the queue (-1 to 1, vendor-specific). */
    signed long         PtmPriority;             /**< Ptm priority for the queue (-1 to 1, vendor-specific). */
    unsigned long       QueueId;                 /**< ID of the queue (unique identifier, typically 1, 2, 3, ..., vendor-specific). */
    unsigned long       LowClassMaxThreshold;    /**< MaxThreshold for the low class of the queue (0 to 100, vendor-specific). */
    unsigned long       LowClassMinThreshold;    /**< MinThreshold for the low class of the queue (0 to 100, vendor-specific). */
    unsigned long       HighClassMinThreshold;   /**< MinThreshold for the high class of the queue (0 to 100, vendor-specific). */
    unsigned long       HighClassMaxThreshold;   /**< MaxThreshold for the high class of the queue (0 to 100, vendor-specific). */
    char                L2DeviceType[32];        /**< Type of Layer 2 device associated with the queue (eth, ptm). */

}WAN_QOS_QUEUE,  *PWAN_QOS_QUEUE;

/**
* @struct WAN_MAPT_CFG
* @brief Contains WAN MAP-T configuration
*/
typedef  struct
_WAN_MAPT_CFG
{
    char          ifName[64];          /**< Interface name (e.g., erouter0). */
    char          brIPv6Prefix[128];   /**< IPv6 prefix for the BR (Border Relay). Valid range: 2000:: to 3FFF:FFFF:FFFF:FFFF:FFFF:FFFF:FFFF:FFFF. */
    char          ruleIPv4Prefix[128]; /**< IPv4 prefix for the rule. Valid ranges for IPv4 addresses: 1.0.0.0 to 127.0.0.0, 128.0.0.0 to 191.255.0.0, 192.0.0.0 to 223.255.255.0. */
    char          ruleIPv6Prefix[128]; /**< IPv6 prefix for the rule. Valid range: 2000:: to 3FFF:FFFF:FFFF:FFFF:FFFF:FFFF:FFFF:FFFF. */
    unsigned int  psidOffset;          /**< Offset value for Port Set Identifier (PSID) (0 to 15, vendor-specific). */
    unsigned int  ratio;               /**< Ratio value (1 to 65,536, vendor-specific). */
    char          pdIPv6Prefix[128];   /**< IPv6 prefix for prefix delegation (e.g., "2001:0db8:85a3::/64"). */

} WAN_MAPT_CFG, *PWAN_MAPT_CFG;

/**
* @struct SELFHEAL_CONFIG
* @brief Contains SelfHeal configuration
*/
typedef struct
_SELFHEAL_CONFIG
{
    unsigned int rebootStatus; /**< Reboot status (0 or 1). 0 indicates no reboot, 1 indicates a reboot. */
}
SELFHEAL_CONFIG, *PSELFHEAL_CONFIG;

/** @} */  //END OF GROUP WAN_HAL_TYPES

/**
 * @addtogroup WAN_HAL_APIS
 * @{
 */

/* wan_hal_Init() function */
/**
* @brief Initialise the wan features.
*
* @param None
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected.
*
*/
int wan_hal_Init();

/* wan_hal_SetWanmode() function */
/**
* @brief Set wanmode value.
*
* @param[in] mode It represents the WAN mode to be set.
*                 \n mode can have any value from enum t_eWanMode.
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected.
*
*/
int wan_hal_SetWanmode(t_eWanMode mode);

/* wan_hal_SetWanConnectionEnable() function */
/**
* @brief Set wanconnection enable value.
*
* @param[in] enable It is an unsigned integer, that represents WanConnectionEnable value to be set.
*                   \n The possible values of enable are:
*                   \n ENABLE : 1, DISABLE : 0.
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected.
*
*/
int wan_hal_SetWanConnectionEnable(unsigned int enable);

/**
* @brief Set SelfHeal Configuration to wanmanager.
*
* @param[in] pSelfHealConfig A pointer to the SELFHEAL_CONFIG structure containing the desired SelfHeal configuration.
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected.
* @remark The caller is responsible for providing a valid memory location for the function argument.
*
*/
int wan_hal_SetSelfHealConfig(PSELFHEAL_CONFIG pSelfHealConfig);

/* wanmgr_hal_GetWanOEUpstreamCurrRate() function */
/**
* @brief Get the current payload bandwidth of the upstream WANoE Connection.
*
* @param[out] pValue A pointer to an unsigned integer, where the current payload bandwidth of the upstream WANoE Connection to be updated.
*                    \n The valid range of the upstream rate is 0 to 2,147,483,647.
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected.
* @remark The caller is responsible for providing a valid memory location for the function argument.
*
*/
int wan_hal_GetWanOEUpstreamCurrRate(unsigned int *pValue);

/* wanmgr_hal_GetWanOEDownstreamCurrRate() function */
/**
* @brief Get the current payload bandwidth of the downstream WANoE Connection.
*
* @param[out] pValue A pointer to an unsigned integer, where the current payload bandwidth of the downstream WANoE Connection to be updated.
*                    \n The valid range of the downstream rate is 0 to 2,147,483,647.
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected.
* @remark The caller is responsible for providing a valid memory location for the function argument.
*
*/
int wan_hal_GetWanOEDownstreamCurrRate(unsigned int *pValue);

/* wan_hal_SetQosConfiguration() function */
/**
* @brief Sets the current QoS configuration.
* @param[in] pQueue A Pointer the structure WAN_QOS_QUEUE which contains the QoS configurations to be set.
* @param[in] QueueNumberOfEntries The number of QoS profiles.
*            \n It is a vendor specific value.
* @param[in] baseifname A pointer to the character array that will hold the Base interface name.
*                         \n The buffer size should be atleast 32 bytes,
*                         \n which is considered as the maximum limit for the interface name, including any null terminators or additional information.
*                         \n The possible values are : erouter0.
* @param[in] wanifname A pointer to the character array that will hold the Wan interface name.
*                        \n The buffer size should be atleast 32 bytes,
*                        \n which is considered as the maximum limit for the interface name, including any null terminators or additional information.
*                        \n The possible values are : erouter0.
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected.
* @remark The caller is responsible for providing a valid memory location for the function argument.
*
*/
int wan_hal_SetQoSConfiguration(PWAN_QOS_QUEUE pQueue, unsigned int QueueNumberOfEntries, const char* baseifname, const char* wanifname);

/* wan_hal_ConfigureIpv4() function */
/**
* @brief configure IPv4 dnsservers, netmask and ip address for the required interface
*
* @param[in] pWanIpv4Cfg Pointer to the structure WAN_IPV4_CFG which contains WAN IPv4 configuration.
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected.
* @remark The caller is responsible for providing a valid memory location for the function argument.
*
*/
int wan_hal_ConfigureIpv4(PWAN_IPV4_CFG pWanIpv4Cfg);

/* wan_hal_UnConfigureIpv4() function */
/**
* @brief unconfigure IPv4 dnsservers, netmask and ip address for the required interface
*
* @param[in] pWanIpv4Cfg Pointer to the structure WAN_IPV4_CFG which contains WAN IPv4 configuration.
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected.
* @remark The caller is responsible for providing a valid memory location for the function argument.
*
*/
int wan_hal_UnConfigureIpv4(PWAN_IPV4_CFG pWanIpv4Cfg);

/* wan_hal_ConfigureIpv6() function */
/**
* @brief Add IPv6 address for the required interface
*
* @param[in] pWanIpv6Cfg Pointer to the structure WAN_IPV6_CFG which contains WAN IPv6 configuration.
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected.
* @remark The caller is responsible for providing a valid memory location for the function argument.
*
*/
int wan_hal_ConfigureIpv6(PWAN_IPV6_CFG pWanIpv6Cfg);

/* wan_hal_UnConfigureIpv4() function */
/**
* @brief Delete IPv6 address for the required interface
*
* @param[in] pWanIpv6Cfg Pointer to the structure WAN_IPV6_CFG which contains WAN IPv6 configuration.
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected.
* @remark The caller is responsible for providing a valid memory location for the function argument.
*
*/
int wan_hal_UnConfigureIpv6(PWAN_IPV6_CFG pWanIpv6Cfg);

/* wan_hal_EnableMapt() function */
/**
* @brief Enable MAP-T for the required interface
*
* @param[in] pMAPTCfg Pointer to the structure WAN_MAPT_CFG which contains WAN MAP-T configuration.
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected.
* @remark The caller is responsible for providing a valid memory location for the function argument.
*
*/
int wan_hal_EnableMapt( PWAN_MAPT_CFG pMAPTCfg );

/* wan_hal_DisableMapt() function */
/**
* @brief Disable MAP-T for the required interface
*
* @param[in] ifName It is a pointer to a constant character array (string) named ifName.
*                  \n The possible values are : erouter0.
*                  \n This parameter represents the name of the interface on which the MAP-T feature is to be disabled.
*                  \n The buffer size should be at least 64 bytes,
*                  \n which is the recommended maximum length for the input string including any null terminators or additional information.
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected.
* @remark The caller is responsible for providing a valid memory location for the function argument.
*
*/
int wan_hal_DisableMapt(const char* ifName);

/**
 * @brief Set/Reset WANoE mode based on the enable flag.
 * @param[in] enable It is an unsigned char type named enable, used to enable or disable WANoE mode.
 *                   \n The use of the const qualifier indicates that the parameter value will not be modified within the function.
 *                   \n The possible values are : 0, 1.
 */
int wan_hal_enableWanOEMode(const unsigned char enable);

/**
 * @brief Get authentication information like ADSL username and password.
 * @param[out] authInfo It is a character pointer to hold the authentication data.
 *                     \n It is a pointer to a character array (string) named authInfo.
 *                     \n This parameter is used to pass a buffer or memory location where the authentication information will be stored.
 *                     \n The buffer size should be at least 256 bytes long and the maximum buffer size is 16384.
 *                     \n A buffer of this size ensures space for the returned value with any null terminators or additional information.
 *                     \n The returned string will be Zero Terminated (ZT).
 *                     \n It is a vendor specific value.
 * @retval RETURN_OK if successful else RETURN_ERR.
 * @remark The caller is responsible for providing a valid memory location for the function argument.
 */
int wan_hal_getAuthInfo(char *authInfo);

/** @} */  //END OF GROUP WAN_HAL_APIS
#endif /* __WAN_HAL_H__ */
