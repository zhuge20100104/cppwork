#! /bin/bash
# 将SELINUX=开头的行，替换为 SELINUX=disabled
sed -i '/^SELINUX=*/c SELINUX=disabled' config

