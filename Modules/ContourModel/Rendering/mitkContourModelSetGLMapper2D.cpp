/*===================================================================

The Medical Imaging Interaction Toolkit (MITK)

Copyright (c) German Cancer Research Center,
Division of Medical and Biological Informatics.
All rights reserved.

This software is distributed WITHOUT ANY WARRANTY; without
even the implied warranty of MERCHANTABILITY or FITNESS FOR
A PARTICULAR PURPOSE.

See LICENSE.txt or http://www.mitk.org for details.

===================================================================*/

#include "mitkContourModelSetGLMapper2D.h"

#include "mitkColorProperty.h"
#include "mitkContourModelSet.h"
#include "mitkPlaneGeometry.h"
#include "mitkProperties.h"
#include <vtkLinearTransform.h>

#include "mitkGL.h"

mitk::ContourModelSetGLMapper2D::ContourModelSetGLMapper2D()
{
}

mitk::ContourModelSetGLMapper2D::~ContourModelSetGLMapper2D()
{
}

void mitk::ContourModelSetGLMapper2D::MitkRender(mitk::BaseRenderer *renderer, mitk::VtkPropRenderer::RenderType /*type*/)
{
    BaseLocalStorage *ls = m_LSH.GetLocalStorage(renderer);

    mitk::DataNode::Pointer dataNode = this->GetDataNode();
    bool visible = true;
    dataNode->GetVisibility(visible, nullptr);

    if (!visible)
        return;

    mitk::ContourModelSet::Pointer input = this->GetInput();

    auto centerOfViewPointZ = renderer->GetCurrentWorldPlaneGeometry()->GetCenter()[2];
    mitk::ContourModelSet::ContourModelSetIterator it = input->Begin();

    mitk::ContourModelSet::ContourModelSetIterator end = input->End();

    while (it != end)
    {
        //we have the assumption that each contour model vertex has the same z coordinate
        auto currentZValue = (*it)->GetVertexAt(0)->Coordinates[2];
        double acceptedDeviationInMM = 5.0;
        //only draw contour if it is visible
        if (currentZValue - acceptedDeviationInMM < centerOfViewPointZ && currentZValue + acceptedDeviationInMM > centerOfViewPointZ){
            this->DrawContour(it->GetPointer(), renderer);
        }
        ++it;
    }

    if (input->GetSize() < 1)
        return;

    ls->UpdateGenerateDataTime();
}

mitk::ContourModelSet *mitk::ContourModelSetGLMapper2D::GetInput(void)
{
  return const_cast<mitk::ContourModelSet *>(static_cast<const mitk::ContourModelSet *>(GetDataNode()->GetData()));
}

void mitk::ContourModelSetGLMapper2D::SetDefaultProperties(mitk::DataNode *node,
                                                           mitk::BaseRenderer *renderer,
                                                           bool overwrite)
{
  node->AddProperty("contour.color", ColorProperty::New(0.9, 1.0, 0.1), renderer, overwrite);
  node->AddProperty("contour.points.color", ColorProperty::New(1.0, 0.0, 0.1), renderer, overwrite);
  node->AddProperty("contour.points.show", mitk::BoolProperty::New(false), renderer, overwrite);
  node->AddProperty("contour.segments.show", mitk::BoolProperty::New(true), renderer, overwrite);
  node->AddProperty("contour.controlpoints.show", mitk::BoolProperty::New(false), renderer, overwrite);
  node->AddProperty("contour.width", mitk::FloatProperty::New(1.0), renderer, overwrite);
  node->AddProperty("contour.hovering.width", mitk::FloatProperty::New(3.0), renderer, overwrite);
  node->AddProperty("contour.hovering", mitk::BoolProperty::New(false), renderer, overwrite);
  node->AddProperty("contour.points.text", mitk::BoolProperty::New(false), renderer, overwrite);
  node->AddProperty("contour.controlpoints.text", mitk::BoolProperty::New(false), renderer, overwrite);

  node->AddProperty("contour.project-onto-plane", mitk::BoolProperty::New(false), renderer, overwrite);

  node->AddProperty("opacity", mitk::FloatProperty::New(1.0f), renderer, overwrite);

  Superclass::SetDefaultProperties(node, renderer, overwrite);
}
