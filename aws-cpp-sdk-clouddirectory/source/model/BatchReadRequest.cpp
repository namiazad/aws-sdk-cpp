﻿/*
* Copyright 2010-2017 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* Licensed under the Apache License, Version 2.0 (the "License").
* You may not use this file except in compliance with the License.
* A copy of the License is located at
*
*  http://aws.amazon.com/apache2.0
*
* or in the "license" file accompanying this file. This file is distributed
* on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
* express or implied. See the License for the specific language governing
* permissions and limitations under the License.
*/

#include <aws/clouddirectory/model/BatchReadRequest.h>
#include <aws/core/utils/json/JsonSerializer.h>
#include <aws/core/utils/memory/stl/AWSStringStream.h>

#include <utility>

using namespace Aws::CloudDirectory::Model;
using namespace Aws::Utils::Json;
using namespace Aws::Utils;

BatchReadRequest::BatchReadRequest() : 
    m_directoryArnHasBeenSet(false),
    m_operationsHasBeenSet(false),
    m_consistencyLevel(ConsistencyLevel::NOT_SET),
    m_consistencyLevelHasBeenSet(false)
{
}

Aws::String BatchReadRequest::SerializePayload() const
{
  JsonValue payload;

  if(m_operationsHasBeenSet)
  {
   Array<JsonValue> operationsJsonList(m_operations.size());
   for(unsigned operationsIndex = 0; operationsIndex < operationsJsonList.GetLength(); ++operationsIndex)
   {
     operationsJsonList[operationsIndex].AsObject(m_operations[operationsIndex].Jsonize());
   }
   payload.WithArray("Operations", std::move(operationsJsonList));

  }

  return payload.View().WriteReadable();
}

Aws::Http::HeaderValueCollection BatchReadRequest::GetRequestSpecificHeaders() const
{
  Aws::Http::HeaderValueCollection headers;
  Aws::StringStream ss;
  if(m_directoryArnHasBeenSet)
  {
    ss << m_directoryArn;
    headers.insert(Aws::Http::HeaderValuePair("x-amz-data-partition", ss.str()));
    ss.str("");
  }

  if(m_consistencyLevelHasBeenSet)
  {
    headers.insert(Aws::Http::HeaderValuePair("x-amz-consistency-level", ConsistencyLevelMapper::GetNameForConsistencyLevel(m_consistencyLevel)));
  }

  return headers;

}




