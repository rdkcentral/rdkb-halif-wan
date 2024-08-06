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
    unsigned long       queueWeight;             /**< Weight of the queue (0 to 100). */
    unsigned long       queuePrecedence;         /**< Precedence of the queue (1 to 4294967295, vendor-specific). */
    unsigned long       REDThreshold;            /**< RED (Random Early Detection) threshold (1 to 100. */
    char                dropAlgorithm[256];      /**< Drop algorithm used by the queue (e.g., DT, RED, WRED, vendor-specific). */
    char                schedulerAlgorithm[256]; /**< Scheduling algorithm used by the queue (e.g., SP, WRR, WFQ, vendor-specific). */
    signed long         shapingRate;             /**< Shaping rate for the queue (-1 to 2147483647, vendor-specific). */
    unsigned long       shapingBurstSize;        /**< Burst size for queue shaping (0 to max burst size, vendor-specific). */
    signed long         MinBitRate;              /**< Minimum bit rate for the queue (-1 to 2147483647, vendor-specific). */
    char                QueueName[256];          /**< Name of the queue (e.g., WAN Q1, WAN Q2, ..., WAN Q10). */
    signed long         DslLatency;              /**< DSL latency for the queue (-1 to 1, vendor-specific). */
    signed long         PtmPriority;             /**< Ptm priority for the queue (-1 to 1, vendor-specific). */
    unsigned long       QueueId;                 /**< ID of the queue (unique identifier, typically 1, 2, 3, ..., vendor-specific). */
    unsigned long       LowClassMaxThreshold;    /**< MaxThreshold for the low class of the queue (0 to 100). */
    unsigned long       LowClassMinThreshold;    /**< MinThreshold for the low class of the queue (0 to 100). */
    unsigned long       HighClassMinThreshold;   /**< MinThreshold for the high class of the queue (0 to 100). */
    unsigned long       HighClassMaxThreshold;   /**< MaxThreshold for the high class of the queue (0 to 100). */
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
    unsigned int rebootStatus; /**< Indicates whether a reboot is required (0: No reboot, 1: Reboot). */
}
SELFHEAL_CONFIG, *PSELFHEAL_CONFIG;

/** @} */  //END OF GROUP WAN_HAL_TYPES

/**
 * @addtogroup WAN_HAL_APIS
 * @{
 */

/**
 * @brief Initializes the WAN features.
 *
 * This function is responsible for setting up the WAN Hardware Abstraction Layer (HAL)
 * and preparing it for operation. This may involve initializing internal data structures,
 * establishing communication with the WAN hardware, and starting any necessary background processes.
 *
 * @returns The status of the operation.
 * @retval RETURN_OK if the initialization is successful.
 * @retval RETURN_ERR if an error occurs during initialization.
 */
int wan_hal_Init();

/**
 * @brief Sets the WAN mode of the device.
 * 
 * This function configures the operational mode of the WAN interface, determining 
 * how the device connects to the wider network (e.g., DSL, Ethernet, or automatic selection).
 *
 * @param[in] mode The desired WAN mode to be set (see `t_eWanMode` for valid options).
 *
 * @returns The status of the operation.
 * @retval RETURN_OK if the WAN mode is set successfully.
 * @retval RETURN_ERR if an error occurs during the configuration process.
 */
int wan_hal_SetWanmode(t_eWanMode mode);

/**
 * @brief Enables or disables the WAN connection.
 *
 * This function controls the activation or deactivation of the WAN interface,
 * allowing the device to connect to or disconnect from the wider network.
 *
 * @param[in] enable Flag to enable (1) or disable (0) the WAN connection.
 *
 * @returns The status of the operation.
 * @retval RETURN_OK if the operation is successful.
 * @retval RETURN_ERR if an error occurs during the operation.
 */
int wan_hal_SetWanConnectionEnable(unsigned int enable);

/**
 * @brief Sets the SelfHeal configuration for the WAN manager.
 *
 * This function applies the desired SelfHeal configuration settings, 
 * which determine how the system should respond to WAN-related errors or failures.
 *
 * @param[in] pSelfHealConfig Pointer to a `SELFHEAL_CONFIG` structure containing the 
 *                           SelfHeal configuration parameters.
 *
 * @returns The status of the operation.
 * @retval RETURN_OK if the configuration is set successfully.
 * @retval RETURN_ERR if an error occurs during configuration.
 */
int wan_hal_SetSelfHealConfig(PSELFHEAL_CONFIG pSelfHealConfig);

/**
 * @brief Retrieves the current payload bandwidth of the upstream WANoE (WAN over Ethernet) connection.
 *
 * This function fetches the real-time rate at which payload data is being transmitted
 * on the upstream WANoE connection. The rate is measured in bits per second.
 *
 * @param[out] pValue A pointer to an unsigned integer variable where the retrieved upstream 
 *                    bandwidth value will be stored.
 *
 * @returns The status of the operation.
 * @retval RETURN_OK if the upstream bandwidth is successfully retrieved.
 * @retval RETURN_ERR if an error occurs during the retrieval process.
 */
int wan_hal_GetWanOEUpstreamCurrRate(unsigned int *pValue);

/**
 * @brief Retrieves the current payload bandwidth of the downstream WANoE (WAN over Ethernet) connection.
 *
 * This function fetches the real-time rate at which payload data is being received
 * on the downstream WANoE connection. The rate is measured in bits per second.
 *
 * @param[out] pValue A pointer to an unsigned integer variable where the retrieved downstream 
 *                    bandwidth value will be stored.
 *
 * @returns The status of the operation.
 * @retval RETURN_OK if the downstream bandwidth is successfully retrieved.
 * @retval RETURN_ERR if an error occurs during the retrieval process.
 */
int wan_hal_GetWanOEDownstreamCurrRate(unsigned int *pValue);

/**
 * @brief Configures the Quality of Service (QoS) settings for the WAN interface.
 *
 * This function applies the provided QoS queue configurations to the specified 
 * base and WAN interfaces. It allows for fine-grained control over how network 
 * traffic is prioritized and managed.
 *
 * @param[in] pQueue An array of `WAN_QOS_QUEUE` structures containing the QoS configurations for each queue.
 * @param[in] QueueNumberOfEntries The number of QoS queue configurations provided in the `pQueue` array.
 * @param[in] baseifname The name of the base interface (e.g., "erouter0").
 * @param[in] wanifname The name of the WAN interface (e.g., "erouter0").
 *
 * @returns The status of the operation.
 * @retval RETURN_OK if the QoS configuration is applied successfully.
 * @retval RETURN_ERR if an error occurs during the configuration process.
 */
int wan_hal_SetQoSConfiguration(PWAN_QOS_QUEUE pQueue, unsigned int QueueNumberOfEntries, const char* baseifname, const char* wanifname);

/**
 * @brief Configures IPv4 settings for the specified WAN interface.
 *
 * This function applies the provided IPv4 configuration parameters to the designated 
 * WAN interface. The configuration includes the IP address, subnet mask, default gateway, 
 * and DNS servers.
 *
 * @param[in] pWanIpv4Cfg Pointer to a `WAN_IPV4_CFG` structure containing the IPv4 configuration details.
 *
 * @returns The status of the operation.
 * @retval RETURN_OK if the configuration is applied successfully.
 * @retval RETURN_ERR if an error occurs during the configuration process.
 */
int wan_hal_ConfigureIpv4(PWAN_IPV4_CFG pWanIpv4Cfg);

/**
 * @brief Removes the IPv4 configuration from the specified WAN interface.
 * 
 * This function clears the IPv4 settings, including the IP address, subnet mask,
 * default gateway, and DNS servers, from the designated WAN interface.
 * 
 * @param[in] pWanIpv4Cfg A pointer to a `WAN_IPV4_CFG` structure containing the interface name 
 *                       and optionally the IPv4 configuration details to be removed.
 *
 * @returns The status of the operation.
 * @retval RETURN_OK if the IPv4 configuration is removed successfully.
 * @retval RETURN_ERR if an error occurs during the unconfiguration process.
 */
int wan_hal_UnConfigureIpv4(PWAN_IPV4_CFG pWanIpv4Cfg);

/**
 * @brief Adds an IPv6 address to the specified WAN interface.
 * 
 * This function assigns the provided IPv6 address, along with its preferred and valid lifetimes, 
 * and DNS servers to the designated WAN interface.
 * 
 * @param[in] pWanIpv6Cfg Pointer to a `WAN_IPV6_CFG` structure containing the IPv6 configuration details.
 *
 * @returns The status of the operation.
 * @retval RETURN_OK if the IPv6 address is added successfully.
 * @retval RETURN_ERR if an error occurs during the configuration process.
 */
int wan_hal_ConfigureIpv6(PWAN_IPV6_CFG pWanIpv6Cfg);

/**
 * @brief Removes an IPv6 address from the specified WAN interface.
 *
 * This function deletes the IPv6 address specified in the `pWanIpv6Cfg` structure
 * from the designated WAN interface.
 *
 * @param[in] pWanIpv6Cfg Pointer to a `WAN_IPV6_CFG` structure containing the IPv6 
 *                       address and interface name to be removed.
 *
 * @returns The status of the operation.
 * @retval RETURN_OK if the IPv6 address is successfully removed.
 * @retval RETURN_ERR if an error occurs during the process.
 */
int wan_hal_UnConfigureIpv6(PWAN_IPV6_CFG pWanIpv6Cfg);

/**
 * @brief Enables MAP-T (Mapping of Address and Port Translation) on the specified WAN interface.
 *
 * This function activates the MAP-T protocol on the designated interface, using the
 * configuration parameters provided in the `pMAPTCfg` structure. MAP-T is used to
 * translate IPv6 addresses and ports to IPv4 equivalents, allowing IPv6-only clients to
 * communicate with IPv4-only servers.
 *
 * @param[in] pMAPTCfg Pointer to a `WAN_MAPT_CFG` structure containing the configuration
 *                     details for MAP-T.
 *
 * @returns The status of the operation.
 * @retval RETURN_OK if MAP-T is enabled successfully.
 * @retval RETURN_ERR if an error occurs during the enablement process.
 */
int wan_hal_EnableMapt( PWAN_MAPT_CFG pMAPTCfg );

/**
 * @brief Disables MAP-T (Mapping of Address and Port Translation) on the specified WAN interface.
 * 
 * This function deactivates the MAP-T protocol on the given interface, 
 * preventing further translation of IPv6 addresses and ports to IPv4 equivalents.
 *
 * @param[in] ifName The name of the WAN interface on which MAP-T is to be disabled (e.g., "erouter0").
 *
 * @returns The status of the operation.
 * @retval RETURN_OK if MAP-T is disabled successfully.
 * @retval RETURN_ERR if an error occurs during the disablement process.
 */
int wan_hal_DisableMapt(const char* ifName);

/**
 * @brief Enables or disables WANoE (WAN over Ethernet) mode.
 * 
 * This function allows you to control whether the WAN interface operates in WANoE mode.
 * When enabled, the device's WAN connection is established over an Ethernet link.
 *
 * @param enable Set to 1 to enable WANoE mode, or 0 to disable it.
 *
 * @returns The status of the operation.
 * @retval RETURN_OK if the operation is successful.
 * @retval RETURN_ERR if an error occurs.
 */
int wan_hal_enableWanOEMode(const unsigned char enable);

/**
 * @brief Retrieves authentication information for the WAN connection.
 *
 * This function fetches authentication credentials, such as the ADSL username and password,
 * required to establish or maintain the WAN connection. The retrieved information is 
 * stored in a buffer provided by the caller.
 *
 * @param[out] authInfo A pointer to a character buffer where the retrieved authentication information
 *                      will be stored. Ensure the buffer is sufficiently large to hold the data
 *                      (minimum 256 bytes, maximum 16384 bytes). The returned string will be null-terminated.
 *
 * @returns The status of the operation.
 * @retval RETURN_OK if the authentication information is retrieved successfully.
 * @retval RETURN_ERR if an error occurs during the retrieval process.
 */
int wan_hal_getAuthInfo(char *authInfo);

/** @} */  //END OF GROUP WAN_HAL_APIS
#endif /* __WAN_HAL_H__ */
