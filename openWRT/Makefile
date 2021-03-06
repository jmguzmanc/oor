#
# Copyright (C) 2012-2013 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=oor
PKG_REV:=45b51adeb0114eff4854ddef820747304a7fa27a
PKG_VERSION:=1.1.1
PKG_RELEASE:=3-WS2

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.bz2
PKG_SOURCE_URL:=git@github.com:jmguzmanc/oor.git
PKG_SOURCE_PROTO:=git
PKG_SOURCE_SUBDIR:=$(PKG_NAME)-$(PKG_VERSION)
PKG_SOURCE_VERSION:=$(PKG_REV)

PKG_LICENSE:=Apache-2.0
PKG_LICENSE_FILES:=LICENSE

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/nls.mk


define Package/oor/default
  MAINTAINER:=Albert Lóepz <alopez@ac.upc.edu>
  URL:=http://www.openoverlayrouter.org
endef

define Package/oor
  SECTION:=net
  CATEGORY:=Network
  TITLE:=Open Overlay Router
  URL:=https://github.com/OpenOverlayRouter
  DEPENDS:= +librt +confuse +kmod-tun +uci +libzmq-nc +libxml2 @IPV6
  $(call Package/oor/default)
endef

define Package/oor/description
  This packet provides support for the Locator-ID Separation Protocol, VXLAN-GPE.
endef


define Build/Compile
	$(call Build/Compile/Default,platform=openwrt CFLAGS="-Wall -std=gnu89 -g -I/usr/include/libxml2 -D_GNU_SOURCE=1")
endef


define Package/oor/install
	$(INSTALL_DIR) $(1)/usr/sbin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/oor/oor $(1)/usr/sbin/
	$(INSTALL_DIR) $(1)/etc/config
	$(INSTALL_CONF) $(PKG_BUILD_DIR)/openWRT/oor.uci.example $(1)/etc/config/oor.example
	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/openWRT/openwrt.init.script $(1)/etc/init.d/oor
endef

$(eval $(call BuildPackage,oor))
