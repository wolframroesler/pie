// Pie watchface configuration dialog
// by Wolfram Rösler 2018-08-02

// Created according to: https://developer.rebble.io/developer.pebble.com/guides/user-interfaces/app-configuration/index.html

module.exports = [
    {
        "type": "heading",
        "defaultValue": "Pie Watchface Configuration"
    },
    {
        "type": "section",
        "items": [
            {
                "type": "color",
                "messageKey": "AMColor",
                "defaultValue": "0x0000FF",
                "label": "Background for AM (00:00-11:59)"
            },
            {
                "type": "color",
                "messageKey": "PMColor",
                "defaultValue": "0xFF0000",
                "label": "Background for PM (12:00-23:59)"
            },
            {
                "type": "color",
                "messageKey": "MinuteHandColor",
                "defaultValue": "0xFFFFFF",
                "label": "Minute hand color"
            },
            {
                "type": "slider",
                "messageKey": "MinuteHandWidth",
                "defaultValue": 11,
                "label": "Minute hand width [Pixels]",
                "min": 1,
                "max": 33,
                "step": 2
            },
            {
                "type": "color",
                "messageKey": "LowBattColor",
                "defaultValue": "0xFF0000",
                "label": "Low battery indicator color"
            },
            {
                "type": "slider",
                "messageKey": "LowBattWidth",
                "defaultValue": 8,
                "label": "Low battery indicator width [Pixels, 0=disable indicator]",
                "min": 0,
                "max": 32,
                "step": 2
            },
            {
                "type": "color",
                "messageKey": "NoBTColor",
                "defaultValue": "0x0000FF",
                "label": "Bluetooth offline indicator color"
            },
            {
                "type": "slider",
                "messageKey": "NoBTWidth",
                "defaultValue": 8,
                "label": "Bluetooth offline indicator width [Pixels, 0=disable indicator]",
                "min": 0,
                "max": 32,
                "step": 2
            }
        ]
    },
    {
    "type": "submit",
    "defaultValue": "Save Settings"
    }
];
