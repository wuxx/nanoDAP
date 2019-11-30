#!/bin/bash

#PROJECTS="
#stm32f103xb_bl                   stm32f103xb_stm32f401re_if
#stm32f103xb_if                   stm32f103xb_stm32f411re_if
#stm32f103xb_stm32f072rb_if       stm32f103xb_stm32f429zi_if
#stm32f103xb_stm32f103rb_if       stm32f103xb_stm32f746zg_if
#stm32f103xb_stm32f207zg_if       stm32f103xb_stm32l476rg_if
#stm32f103xb_stm32f334r8_if       stm32f103xb_ublox_evk_odin_w2_if
#"

#PROJECTS="stm32f103xb_bl stm32f103xb_stm32f103rb_if"

PROJECTS="stm32f103xb_stm32f103rb_if"


for PROJECT in ${PROJECTS}
do
    echo ${PROJECT}
    progen generate -f projects.yaml -p ${PROJECT} -t uvision
done

