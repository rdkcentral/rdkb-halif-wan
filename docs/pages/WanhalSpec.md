# WAN HAL Documentation

## Acronyms

- `HAL` \- Hardware Abstraction Layer
- `RDK-B` \- Reference Design Kit for Broadband Devices
- `OEM` \- Original Equipment Manufacture

## Description

The below diagram describes the high-level software architecture of the WAN HAL module stack.

```mermaid
flowchart TD;
    RDK-BSTACK[Caller] <-->
    CcspMoCA[HAL Interface - wan_hal.h\n`HAL IF Specification / Contract Requirement] <-->
    MoCAHAL["HAL (libhal_wan)\nVendor Implementation"] <-->
    VendorSoftware[Drivers\nVendor Implementation]
```

The WAN Hardware Abstraction Layer (HAL) is a software module that provides a standardized interface for managing and monitoring Wide Area Network (WAN) connections on a device. This module allows applications to interact with the underlying WAN hardware without needing to know the specifics of its implementation.

### Key functionalities of the WAN HAL include:

- **WAN Mode Configuration:**
  - Enabling/disabling the WAN interface.
  - Selecting the WAN mode (e.g., DSL-only, Ethernet-only, auto-selection).
  - Configuring self-heal mechanisms for automatic recovery from WAN failures.
- **Network Configuration:**
  - Setting up IPv4 and IPv6 addresses, subnet masks, gateways, and DNS servers.
  - Enabling and configuring MAP-T (Mapping of Address and Port Translation) for IPv6 to IPv4 transition.
  - Managing Quality of Service (QoS) settings to prioritize network traffic.
- **Monitoring and Statistics:**
  - Retrieving the current upstream and downstream bandwidth usage of the WAN connection.
  - Obtaining authentication information (e.g., ADSL username and password).
- **Additional Features:**
  - Enabling WAN over Ethernet (WANoE) mode.
  - Retrieving the MoCA module reset count.

## Component Runtime Execution Requirements

### Initialization and Startup

The below initialization API provides an opportunity for the HAL code to initialize the appropriate DB's, start threads, etc.

The client is expected to call the corresponding API during the boot sequence.

The `wan_hal_Init()` function is essential for initializing the WAN Hardware Abstraction Layer. It sets up internal data structures, prepares the underlying WAN hardware, and potentially starts background threads for managing the WAN connection. This function is called during the device's boot sequence and blocks until the WAN interface is ready for use.

## Threading Model

The interface is not thread safe.

Vendors may implement internal threading and event mechanisms to meet their operational requirements. These mechanisms must be designed to ensure thread safety when interacting with HAL interface. Proper cleanup of allocated resources (e.g., memory, file handles, threads) is mandatory when the vendor software terminates or closes its connection to the HAL.

This interface is not inherently required to be thread-safe. It is the responsibility of the calling module or component to ensure that all interactions with the APIs are properly synchronised.

## Process Model

All APIs are expected to be called from multiple processes. Due to this concurrent access, vendors must implement protection mechanisms within their API implementations to handle multiple processes calling the same API simultaneously. This is crucial to ensure data integrity, prevent race conditions, and maintain the overall stability and reliability of the system.

## Memory Model

**Caller Responsibilities:**

- Manage memory passed to specific functions as outlined in the API documentation. This includes allocation and deallocation to prevent leaks.

**Module Responsibilities:**

- Modules must allocate and de-allocate memory for their internal operations, ensuring efficient resource management.
- Modules are required to release all internally allocated memory upon closure to prevent resource leaks.
- All module implementations and caller code must strictly adhere to these memory management requirements for optimal performance and system stability. Unless otherwise stated specifically in the API documentation.
- All strings used in this module must be zero-terminated. This ensures that string functions can accurately determine the length of the string and prevents buffer overflows when manipulating strings.

TODO:
State a footprint requirement. Example: This should not exceed XXXX KB.

## Power Management Requirements

The HAL is not involved in any of the power management operations.

## Asynchronous Notification Model

There are no asynchronous notifications.

## Blocking calls

**Synchronous and Responsive:** All APIs within this module should operate synchronously and complete within a reasonable timeframe based on the complexity of the operation. Specific timeout values or guidelines may be documented for individual API calls.

**Timeout Handling:** To ensure resilience in cases of unresponsiveness, implement appropriate timeouts for API calls where failure due to lack of response is a possibility. Refer to the API documentation for recommended timeout values per function.

**Non-Blocking Requirement:** Given the single-threaded environment in which these APIs will be called, it is imperative that they do not block or suspend execution of the main thread. Implementations must avoid long-running operations or utilize asynchronous mechanisms where necessary to maintain responsiveness.

TODO:
As we state that they should complete within a time period, we need to state what that time target is, and pull it from the spec if required. Define the timeout requirement.

## Internal Error Handling

**Synchronous Error Handling:** All APIs must return errors synchronously as a return value. This ensures immediate notification of errors to the caller.
**Internal Error Reporting:** The HAL is responsible for reporting any internal system errors (e.g., out-of-memory conditions) through the return value.
**Focus on Logging for Errors:** For system errors, the HAL should prioritize logging the error details for further investigation and resolution.

## Persistence Model

There is no requirement for HAL to persist any setting information. The caller is responsible for persisting any settings related to their implementation.


## Nonfunctional requirements

Following non functional requirement should be supported by the component.

## Logging and debugging requirements

The component is required to record all errors and critical informative messages to aid in identifying, debugging, and understanding the functional flow of the system. Logging should be implemented using the syslog method, as it provides robust logging capabilities suited for system-level software. The use of `printf` is discouraged unless `syslog` is not available.

All HAL components must adhere to a consistent logging process. When logging is necessary, it should be performed into the `wan_vendor_hal.log` file, which is located in either the `/var/tmp/` or `/rdklogs/logs/` directories.

Logs must be categorized according to the following log levels, as defined by the Linux standard logging system, listed here in descending order of severity:

- **FATAL:** Critical conditions, typically indicating system crashes or severe failures that require immediate attention.
- **ERROR:** Non-fatal error conditions that nonetheless significantly impede normal operation.
- **WARNING:** Potentially harmful situations that do not yet represent errors.
- **NOTICE:** Important but not error-level events.
- **INFO:** General informational messages that highlight system operations.
- **DEBUG:** Detailed information typically useful only when diagnosing problems.
- **TRACE:** Very fine-grained logging to trace the internal flow of the system.
- 
Each log entry should include a timestamp, the log level, and a message describing the event or condition. This standard format will facilitate easier parsing and analysis of log files across different vendors and components.

## Memory and performance requirements

**Client Module Responsibility:** The client module using the HAL is responsible for allocating and deallocating memory for any data structures required by the HAL's APIs. This includes structures passed as parameters to HAL functions and any buffers used to receive data from the HAL.

**Vendor Implementation Responsibility:** Third-party vendors, when implementing the HAL, may allocate memory internally for their specific operational needs. It is the vendor's sole responsibility to manage and deallocate this internally allocated memory.

## Quality Control

To ensure the highest quality and reliability, it is strongly recommended that third-party quality assurance tools like `Coverity`, `Black Duck`, and `Valgrind` be employed to thoroughly analyze the implementation. The goal is to detect and resolve potential issues such as memory leaks, memory corruption, or other defects before deployment.

Furthermore, both the HAL wrapper and any third-party software interacting with it must prioritize robust memory management practices. This includes meticulous allocation, deallocation, and error handling to guarantee a stable and leak-free operation.

## Licensing

WAN HAL implementation is expected to be released under the Apache License 2.0.

## Build Requirements

The source code should be capable of, but not be limited to, building under the Yocto distribution environment. The recipe should deliver a shared library named as `libhal_wan.so`.

## Variability Management

The role of adjusting the interface, guided by versioning, rests solely within architecture requirements. Thereafter, vendors are obliged to align their implementation with a designated version of the interface. As per Service Level Agreement (SLA) terms, they may transition to newer versions based on demand needs.

Each API interface will be versioned using [Semantic Versioning 2.0.0](https://semver.org/), the vendor code will comply with a specific version of the interface.

## WAN or Product Customization

None

## Interface API Documentation

All HAL function prototypes and datatype definitions are available in `wan_hal.h` file.

1.  Components/Process must include `wan_hal.h` to make use of WAN hal capabilities.
2.  Components/Process should add linker dependency for `libhal_wan.so`

## Theory of operation and key concepts

### Object Lifecycles:

- **WAN Interface:** The WAN interface is represented implicitly through the ifIndex parameter passed to most functions. Its lifecycle (creation, configuration, and destruction) is managed outside the HAL.
- **Configuration Structures:** Structures like moca_cfg_t, WAN_IPV4_CFG, etc., are temporary data containers used to pass configuration data into the HAL functions. Their lifecycle is managed by the calling code.
  
### Method Sequencing:

1. **Initialization:** Call `wan_hal_Init()` once during system startup to initialize internal data structures and the underlying WAN hardware. This function must complete successfully before any other WAN HAL function is called.
2. **Configuration:** Use the various configuration functions (e.g., `moca_SetIfConfig`, `wan_hal_SetWanmode`, `wan_hal_ConfigureIpv4`) to set desired parameters for the WAN interface. These functions can be called in any order after initialization.
3. **Information Retrieval:** Functions like `moca_IfGetDynamicInfo` and `moca_IfGetStats` can be called anytime after initialization to fetch real-time status and statistics.
4. **Event Handling:** Register a callback function using `moca_associatedDevice_callback_register` to receive notifications about MoCA client activation/deactivation events.

### State-Dependent Behavior:

- **ACA Process:** The ACA-related functions represent a stateful process that can be configured, started, stopped, and monitored for status and results.
- **Implicit State:** The current configuration of the WAN interface (e.g., enabled/disabled, WAN mode, IP settings) defines its operational state.

## Sequence Diagram

```mermaid
sequenceDiagram
title WAN HAL Sequence Diagram
participant Caller
participant WAN HAL
participant Vendor
Note over Caller: Init once during bootup, Needed for Dependent API's. <br> Ignore this if caller doesn't have any Dependent API's
Caller->>WAN HAL: wan_hal_Init()
WAN HAL->>Vendor: 
Vendor ->>WAN HAL: 
WAN HAL->>Caller: wan_hal_Init() return

Caller->>WAN HAL: wan_hal_SetXXX()
WAN HAL->>Vendor: 
Vendor ->>WAN HAL: 
WAN HAL->>Caller: wan_hal_SetXXX() return

Caller->>WAN HAL: wan_hal_GetXXX()
WAN HAL->>Vendor: 
Vendor ->>WAN HAL: 
WAN HAL->>Caller: wan_hal_GetXXX() return

Caller->>WAN HAL: wan_hal_ConfigureXXX()
WAN HAL->>Vendor: 
Vendor ->>WAN HAL: 
WAN HAL->>Caller: wan_hal_ConfigureXXX() return

Caller->>WAN HAL: wan_hal_UnConfigureXXX()
WAN HAL->>Vendor: 
Vendor ->>WAN HAL: 
WAN HAL->>Caller: wan_hal_UnConfigureXXX() return

Caller->>WAN HAL: wan_hal_EnableMapt()
WAN HAL->>Vendor: 
Vendor ->>WAN HAL: 
WAN HAL->>Caller: wan_hal_EnableMapt() return

Caller->>WAN HAL: wan_hal_DisableMapt()
WAN HAL->>Vendor: 
Vendor ->>WAN HAL: 
WAN HAL->>Caller: wan_hal_DisableMapt() return

Caller->>WAN HAL: wan_hal_enableWanOEMode()
WAN HAL->>Vendor: 
Vendor ->>WAN HAL: 
WAN HAL->>Caller: wan_hal_enableWanOEMode() return

Caller->>WAN HAL: wan_hal_getAuthInfo()
WAN HAL->>Vendor: 
Vendor ->>WAN HAL: 
WAN HAL->>Caller: wan_hal_getAuthInfo() return
```
