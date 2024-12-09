idf_component_register(SRCS "ui_conf.c" "core/ui.c" "display/dispDriver.c" "fonts/fonts.c" "images/image.c" "indev/indevDriver.c" "widgets/custom.c" "widgets/parameter.c" "widgets/text.c" "widgets/wave.c"
                    INCLUDE_DIRS "." "core" "display" "fonts" "images" "indev" "widgets"
                    PRIV_REQUIRES "u8g2" "Button"
)