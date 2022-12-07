#!/usr/bin/env python3

from dataclasses import dataclass
from BasePluginArgs import BasePluginArgs

@dataclass
class ResourceMonitorPluginArgs(BasePluginArgs):
    _pluginNamespace: str="eosio"
    _pluginName: str="resource_monitor_plugin"
    resourceMonitorIntervalSeconds: int=None
    _resourceMonitorIntervalSecondsNodeosDefault: int=2
    _resourceMonitorIntervalSecondsNodeosArg: str="--resource-monitor-interval-seconds"
    resourceMonitorSpaceThreshold: int=None
    _resourceMonitorSpaceThresholdNodeosDefault: int=90
    _resourceMonitorSpaceThresholdNodeosArg: str="--resource-monitor-space-threshold"
    resourceMonitorNotShutdownOnThresholdExceeded: bool=None
    _resourceMonitorNotShutdownOnThresholdExceededNodeosDefault: bool=False
    _resourceMonitorNotShutdownOnThresholdExceededNodeosArg: str="--resource-monitor-not-shutdown-on-threshold-exceeded"
    resourceMonitorWarningInterval: int=None
    _resourceMonitorWarningIntervalNodeosDefault: int=30
    _resourceMonitorWarningIntervalNodeosArg: str="--resource-monitor-warning-interval"

def main():
    pluginArgs = ResourceMonitorPluginArgs()
    print(pluginArgs.supportedNodeosArgs())
    exit(0)

if __name__ == '__main__':
    main()
