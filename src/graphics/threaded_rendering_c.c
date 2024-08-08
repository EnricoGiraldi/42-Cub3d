/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threaded_rendering_c.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhrabar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 16:01:16 by ihhrabar          #+#    #+#             */
/*   Updated: 2024/06/08 16:01:17 by ihhrabar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

// dinfo.tgt_clip = dinfo.tgt_quad;
// dinfo.tgt_clip.b.x--;
void	mt_draw_image_into(t_drawing_thread *thread)
{
	int			ssize;
	int			tsize;
	t_draw_info	dinfo;

	dinfo = thread->data.drawing.info;
	ssize = dinfo.src_quad.b.x - dinfo.src_quad.a.x;
	tsize = dinfo.tgt_quad.b.x - dinfo.tgt_quad.a.x;
	dinfo.src_quad.a.x = ceil((double)ssize * thread->min_range);
	dinfo.src_quad.b.x = floor((double)ssize * thread->max_range);
	dinfo.tgt_quad.a.x += ceil((double)tsize * thread->min_range);
	dinfo.tgt_quad.b.x -= floor((double)tsize * (1.0 - thread->max_range));
	image_draw_into(thread->data.drawing.target,
		thread->data.drawing.source, dinfo);
}

void	mt_draw_scene(t_drawing_thread *thread)
{
	t_scene	*scene;

	scene = thread->data.scene;
	draw_ceil_floor_colors(scene, thread->min_range, thread->max_range);
	raycast_region(scene, thread->min_range, thread->max_range,
		scene->timing.draw_interp);
	draw_floors_and_ceilings(scene, thread->min_range, thread->max_range);
}
