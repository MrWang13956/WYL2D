require recipes-graphics/imx-gpu-viv/imx-gpu-viv-6.inc

DEPENDS_append_mx8 = " patchelf-native"

EXTRA_PROVIDES_remove = "virtual/libopenvx"
PROVIDES_OPENVX       = ""
PROVIDES_OPENVX_mx8   = "virtual/libopenvx"
PROVIDES_OPENVX_mx8mm = ""
PROVIDES += "${PROVIDES_OPENVX}"

PACKAGES =+ "libnn-imx"

GLES3_HEADER_REMOVALS_mx8mn = "gl32.h"
GLES3_HEADER_REMOVALS_mx8qxp_remove = "gl32.h"

do_install_append () {

    if [ "${IS_MX8}" = "1" ]; then
        # Change libvulkon.so driver soname, so that it does not clash with the
        # vulkan-loader libvulkan.so
        patchelf --set-soname libvulkan_VSI.so.1 ${D}${libdir}/vulkan/libvulkan_VSI.so
        mv ${D}${libdir}/vulkan/libvulkan_VSI.so ${D}${libdir}/libvulkan_VSI.so
        rm -rf ${D}${libdir}/vulkan
    fi
}

FILES_libgbm-imx_mx8 = "${libdir}/libgbm*${SOLIBS}"

FILES_libvulkan-imx = "${libdir}/libvulkan_VSI${SOLIBS} ${libdir}/libSPIRV_viv${SOLIBS}"
FILES_libvulkan-imx-dev = "${includedir}/vulkan ${libdir}/libvulkan_VSI${SOLIBSDEV}"

FILES_libopenvx-imx = "${libdir}/libOpenVX*${SOLIBS} ${libdir}/libOvx*${SOLIBS} ${libdir}/libovx*${SOLIBS}"
FILES_libopenvx-imx-dev = "${includedir}/VX"
RDEPENDS_libopenvx-imx = "libnn-imx"

FILES_libnn-imx = "${libdir}/libNN*${SOLIBS} ${libdir}/libneuralnetworks${SOLIBS}"

FILES_libopencl-imx = "${libdir}/libOpenCL${SOLIBS} \
                       ${libdir}/libVivanteOpenCL${SOLIBS} \
                       ${libdir}/libLLVM_viv${SOLIBS} \
                       ${sysconfdir}/OpenCL/vendors/Vivante.icd"

RDEPENDS_libopenvg-imx += "${@bb.utils.contains('DISTRO_FEATURES', 'systemd', 'systemd-gpuconfig', '', d)}"