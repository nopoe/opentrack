/* Copyright (c) 2012 Patrick Ruoff
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 */

#ifndef FTNOIR_TRACKER_PT_SETTINGS_H
#define FTNOIR_TRACKER_PT_SETTINGS_H

#include "opentrack/options.hpp"
using namespace options;

struct settings_pt : opts
{
    value<QString> camera_name;
    value<int> cam_res_x,
               cam_res_y,
               cam_fps,
               threshold,
               min_point_size,
               max_point_size;

    value<int> m01_x, m01_y, m01_z;
    value<int> m02_x, m02_y, m02_z;

    value<int> t_MH_x, t_MH_y, t_MH_z;

    value<int> clip_ty, clip_tz, clip_by, clip_bz;
    value<int> active_model_panel, cap_x, cap_y, cap_z;
    
    value<int> fov;
    
    value<bool> dynamic_pose;

    settings_pt() :
        opts("tracker-pt"),
        camera_name(b, "camera-name", ""),
        cam_res_x(b, "camera-res-width", 640),
        cam_res_y(b, "camera-res-height", 480),
        cam_fps(b, "camera-fps", 30),
        threshold(b, "threshold-primary", 128),
        min_point_size(b, "min-point-size", 10),
        max_point_size(b, "max-point-size", 50),
        m01_x(b, "m_01-x", 0),
        m01_y(b, "m_01-y", 0),
        m01_z(b, "m_01-z", 0),
        m02_x(b, "m_02-x", 0),
        m02_y(b, "m_02-y", 0),
        m02_z(b, "m_02-z", 0),
        t_MH_x(b, "model-centroid-x", 0),
        t_MH_y(b, "model-centroid-y", 0),
        t_MH_z(b, "model-centroid-z", 0),
        clip_ty(b, "clip-ty", 0),
        clip_tz(b, "clip-tz", 0),
        clip_by(b, "clip-by", 0),
        clip_bz(b, "clip-bz", 0),
        active_model_panel(b, "active-model-panel", 0),
        cap_x(b, "cap-x", 0),
        cap_y(b, "cap-y", 0),
        cap_z(b, "cap-z", 0),
        fov(b, "camera-fov", 56),
        dynamic_pose(b, "dynamic-pose-resolution", true)
    {}
};

#endif //FTNOIR_TRACKER_PT_SETTINGS_H
